while (true){

    1. app.fqdns DB 파일 읽어서 특정 키워드가 있는 domain만 찾아냄
        std::unordered_set으로 select로 뽑은 domain 중복 제거
        std::unordered_map<std::string, bool>로 keyword 포함 여부 확인
    
    2. 이미 검사된 domain 제거
        how? 스크린샷 저장한 DB에서 domain name을 statement로 설정하여 검사
    
    3. 2에서 남은 목록을 대상으로 스크린샷 추출
        wpl.json 활용
        wpl.json 공부하면 바로 이해됨 -> environment.json, result.json도 왜 나오는 지 알거임

    4. [domain name + 스크린샷 추출 날짜 + 스크린 샷]으로 DB table SQLite에 저장

}