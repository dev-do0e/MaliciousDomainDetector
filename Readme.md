MaliciousDomainDetector

========================================

11월 26일 00시 26분
현재 진행 상황
개발 방향성과 class architecture 설계완료

step 1. 완료
SQLite에서 데이터 Fetch 구현 완료했고 리눅스에서 빌드 진행해서 1분 마다 Domain 10개 나오는 지 확인하면 됨

step 2. 완료
findKeywordInDomain 구현
새롭게 추가된 Domain이 있는 지 확인되었으면 
containsKeywordInDns에서 Domain에 keyword가 포함되어 있는 지 확인 

step 3. 
중복체크 해야함
findDomainDifferences 함수 구현
fqdnsDomains과 checkedDomains 비교 진행해서
fqdnsDomains에 새롭게 추가된 Domain이 있는지 확인

step 4. 사진찍어서 저장
========================================

목적 : Lampad가 인식한 Domain에서 악성 Domain이 있는 지 체크 및 있다면 Lampad-W API 사용하여 screenshot

큰 틀
0. ./MailciousDomainDector
1. 1분에 한 번씩 SQLite DB : fqdns에서 domain name을 체크.
    vector 2개 선언
    a. vector<std::string> fqdnsDomains;
        -> fqdns의 DNS 전체.
    b. vector<std::string> checkedDomains;
        -> fqdns의 DNS에서 이미 체크한 DNS
    **위 두개의 vector는 특정 조건에 의해 정렬되어 있어야함.
    fqdnsDomains.size() > checkedDomains.size() 조건이 성립되면 새롭게 추가된 DNS가 무엇인지 탐색
2. 새롭게 추가된 DNS에 Keyword가 포함되어 있는 지 확인
    a. Keyword 목록은 외부 입력
        -> Json string array
3. 새롭게 추가된 DNS가 Keyword를 포함하고 있다면 해당 URL를 Lampad-W로 보내버리고 screenShot 남기기.

class 정의
1. DomainScanner
    큰 틀의 1~2번을 수행.
2. SqlDataFetcher
    SQLite의 DB 테이블 값 가져오기
3. JsonParser
    Keyword와 Lampad-W 정보를 담을 수 있는 json file parsing
4. RestAPI
    Lampad-W로 보내버리기

SqlDataFetcher Class 구현법
SqlDataFetcher Class 호출할 때 생성자로 DB 파일 지정해서 먼저 열 수 있도록 해놓음
DB를 먼저 열어놓는다고 해도 DML Query가 어떤것인지에 따라 아웃풋 폼이 달라지기에 DB에서 필요한 값이 있다면 그때마다 함수를 새로 구현해야함
