const fs = require('fs');
const puppeteer = require('puppeteer');
const PuppeteerHar = require('puppeteer-har');

const start = async (parameters, result) => {
	// exception handling: URLs to ignore even when 4XX or 5XX is found
	console.log("Set ignore list");
	let ignoreList = new Set();
	if (parameters.ignorelist) for (element of parameters.ignorelist) ignoreList.add(element);

	// launch browser
	console.log("Launch browser");
	const browser = await puppeteer.launch({ headless: "new", "executablePath": "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe" }, { args: ['--allow-outdated-plugins', '--allow-running-insecure-content'] });
	const page = await browser.newPage();
	await page.setCacheEnabled(false);

	// load page
	// c.f. how to implement login: https://stackoverflow.com/questions/50074799/how-to-login-in-puppeteer
	console.log("Load page");
	const harInstance = new PuppeteerHar(page);
	await harInstance.start();
	let startTime = new Date();
	// try to load page up to three times, since page load timeout can occur even in "normal" situation
	for (let i = 0; i < 3; ++i) {
		try {
			await page.goto(parameters.url, { timeout: parameters.timeout > 10 ? parameters.timeout * 1000 : 10000 });
			break;
		} catch (e) {
			if (i < 2) {
				console.log("Exception occurred on opening page. Execution will continue after 5 seconds. Exception details: " + e.message);
				await new Promise(r => setTimeout(r, 5000));
				continue;
			} else throw e;
		}
	}

	// get results
	console.log("Get results");
	const har = await harInstance.stop();
	const metrics = await page.metrics();
	const hrefs = await page.evaluate(
		() => Array.from(
			document.querySelectorAll('a[href]'),
			a => a.getAttribute('href')
		)
	);
	const screenshot = await page.screenshot({ fullPage: true });
	await browser.close();

	// access raw data(for debug only)
	// const fs = require('fs');
	// fs.writeFileSync('har.json', JSON.stringify(har));
	// fs.writeFileSync('metrics.json', JSON.stringify(metrics));
	// fs.writeFileSync('links.json', JSON.stringify(hrefs1));
	// fs.writeFileSync('screenshot.png', screenshot);

	// update test result
	console.log("Build test result");
	result.details = {
		elapsed: new Date() - startTime,
		url: parameters.url,
		metrics: {
			TaskDuration: Math.round(metrics.TaskDuration * 1000),
			ScriptDuration: Math.round(metrics.ScriptDuration * 1000)
		},
		resources: refineHar(har),
		links: hrefs.filter(value => value[0] != '#' && value != '/')
	};
	if (parameters.savescreenshot == true) result.details.screenshot = Buffer.from(screenshot).toString('base64'); // save screenshot only when designated

	// if there's a resource with HTTP status code 400 or higher, treat is as failure
	console.log("Determine success / failure");
	let erroneous_url = "";
	for (const element of result.details.resources)
		if (element.statuscode >= 400 && !ignoreList.has(element.url))
			erroneous_url = erroneous_url + element.url + ' (' + element.statuscode + ')\n';
	if (erroneous_url) {
		result.success = false;
		result.details = "페이지 로딩중 일부 자원의 요청에 실패했습니다(URL + status code):\n" + erroneous_url;
	}
}

const refineHar = (har) => har.log.entries.map((entry) => {
	console.log("Refine HAR");
	let result = {
		method: entry.request.method,
		url: entry.request.url,
		statuscode: entry.response.status,
		filesize: entry.response.content.size,
		serverip: entry.serverIPAddress,
		timings: entry.timings
	};

	return result;
})

console.log("Starting up");
(async () => {
	// prepare for test environment
	console.log("Prepare for environment");
	const environment = JSON.parse(fs.readFileSync("environment.json", { encoding: 'utf-8' }));
	let result = {
		timestamp: Math.trunc(Date.now() / 1000),
		name: environment.name,
		template: environment.template,
		success: true,
		details: {}
	};

	// run the test
	try {
		console.log("Start test");
		await start(environment, result);
		console.log("Writing result");
		fs.writeFileSync('result.json', JSON.stringify(result));
		console.log("Done");
	} catch (e) {
		console.log("Exception occurred");
		result.success = false;
		result.details = e.message;
		fs.writeFileSync('result.json', JSON.stringify(result));
		process.exit(-1);
	}
})();
