# DEEPSLEEP by Unreal Engine 5.4.3



![Title](https://github.com/user-attachments/assets/9791fccb-baf9-4a20-bd8c-5561cc55d286)


- Dev Discord Link : https://discord.gg/PuKnyCGV4Y

-----------------------------------------------------------

# 프로젝트 PC 최소사양

### Windows
1. OS : Windows 10 22H2 Build
2. Desktop CPU : intel i5 6500 or AMD Ryzen 5 1600
3. Laptop CPU : intel i5 8300H 
4. RAM : DDR4 Memory 16GB
5. GPU : Nvidia Geforce GTX 1050(4G) or AMD Radeon RX 560(4G)
6. IDE 1 : Visual studio Version : 17.8(MSVC 14.38.33130)
7. IDE 2 : Rider 2024.1.4

### Mac
1. OS : macOS 14 Sonoma
2. Processor : Apple M2(need to Nanite & Lumen)
3. RAM : 16g
4. IDE 1 : Xcode 15
5. IDE 2 : Rider 2024.1.4

-----------------------------------------------------------

# 프로젝트 PC 권장사양

### Windows
1. OS : Windows 11 23H2 Build
2. Desktop CPU : intel i7 10700 or AMD Ryzen 7 3700
3. Laptop CPU : intel i7 12700H or AMD Ryzen 7 6800H
4. RAM : DDR4 Memory 32GB
5. GPU : Nvidia Geforce RTX 2060 or AMD Radeon RX 6500XT
6. IDE 1 : Visual studio Version : 17.8(MSVC 14.38.33130)
7. IDE 2 : Rider 2024.1.4

### Mac
1. OS : macOS 14 Sonoma
2. Processor : Apple M3 pro (need to Nanite & Lumen - Hardware RTcore)
3. RAM : 32g
4. IDE 1 : Xcode 15
5. IDE 2 : Rider 2024.1.4

-----------------------------------------------------------

# 프로젝트 작업 시 설치법 및 주의사항
(Korean)

프로젝트 파일 관리는 Content(에셋 폴더)를 제외한 나머지 중요 파일은
모두 해당 레포지토리에 보관됩니다.(Source, Config, .uproject)

Content(에셋 폴더) 다운로드는 SVN 서버를 사용하며,
언리얼의 리비전 컨트롤을 사용합니다.

리비전 컨트롤 개념은 아래 언리얼 문서에서 확인해주세요.

### 언리얼 문서 : https://docs.unrealengine.com/4.27/ko/ProductionPipelines/SourceControl/InEditor/


참고 : 기존 SVN의 서버 주소도 변경되었습니다.
-----------------------------------------------------------

#브랜치 관리법 

###Master <- Develop <- Feature/[기능이름]

구조로 브랜치를 관리한다.

1. 기본적으로 Develop 브랜치에서 작업하며, 기능을 추가할 때마다 Feature 브랜치를 생성하여 작업한다.

2. Feature 브랜치에서 작업이 완료되면 dev브랜치로 merge한다.

3. Develop 브랜치에서 작업이 완료되면 main브랜치로 merge한다.

- Master 브랜치는 게임의 최종 빌드 버전이다.

-----------------------------------------------------------

- SVN 소스컨트롤 Nextday 서버주소
```
https://nextday.iptime.org:443/svn/DEEPSLEEP_5.4/trunk
```
- Github 레포지토리 주소
```
https://github.com/Parkyongseok1120/DEEPSLEEP_NextdayStudio
```
-----------------------------------------------------------

가장 중요한 점은 더 이상 에픽게임즈 런처 내의 엔진을 사용하지 않으며,

Github 쪽의 개발자용 언리얼 엔진을 사용합니다.
### (*단, macOS의 경우 에픽게임즈 언리얼 엔진 버전을 사용합니다.)

-----------------------------------------------------------

# 프로젝트 다운 전 주의사항

1. 해당 프로젝트의 주소나, SVN주소를 유출하지 않습니다.
2. SVN와 언리얼 깃허브 버전을 다운 시 엑세스할 계정이 필요하므로, 신규 참여자는 관리자에게 디스코드로 연락해주시기 바랍니다.
3. 에픽게임즈 런처의 엔진으로 해당 프로젝트를 실행하지 않습니다.
4. 해당 프로젝트의 모든 저작권은 박용석(NEXTDAY Studio - DEEPSLEEP 프로젝트 디렉터)에게 있습니다.
5. 해당 프로젝트를 사용하여 포트폴리오 내용을 작성하는 것까지는 가능하나, 이외 외부에 함부로 유출하지 않습니다.
6. MacOS의 경우는 깃허브 언리얼 엔진을 사용하지 않고, 에픽게임즈 런처의 엔진을 사용하시기 바랍니다.


-----------------------------------------------------------

# 프로젝트 실행을 위한 세팅

### 1. Gihtub Unreal engine 5.4.3 다운로드

Github version Unreal Engine 5.4.3 Link(계정 엑세스 관리자 요청 필요)
```
https://github.com/Parkyongseok1120/UnrealEngine
```


해당 프로젝트에 참여하는 모든 인원은 GIthub 언리얼 엔진 페이지에서 Unreal engine 5.4.3 릴리즈 버전을 다운 받아주시길 바랍니다.

엔진은 더이상 해당 버전에서 마이너 업데이트만 업데이트하고 (5.4.2~5.4.x)

메이저 업데이트의 경우는 실시하지 않을 것입니다.(5.5.0~5.6.0등등)

-----------------------------------------------------------

### 2. 비주얼 스튜디오 설치(LTSC 17.8)

비주얼 스튜디오 버전은 17.8버전을 사용합니다.(현재 17.10이 최신버전)

최신버전을 사용하지 않는 이유는 Github에서 클론하여 받은 언리얼 엔진 5.4.1 릴리즈 소스코드를 빌드할 떄 

비주얼 스튜디오 컴파일러 msvc 버전이 14.38.33130 이어야 합니다.

신버전은 msvc버전이 14.40버전으로 호환이 되질 않아 빌드가 불가능합니다.


해당 Visual studio 2022 LTSC 17.8 버전의 설치 파일은 팀 디스코드 공지에 올려두었습니다.

-----------------------------------------------------------

### 3. 엔진 빌드 완료시 

언리얼 엔진 빌드가 완료되고 정상적으로 언리얼 엔진이 켜졌을 경우, 

프로젝트 폴더를 구성할시에, 먼저 소스파일을 다운 받도록 합니다.

-----------------------------------------------------------

### 4. Github 프로젝트 다운로드

Github Desktop 이나 Github Fork 를 다운 받아서 해당 프로젝트를 클론하고서 프로젝트를 컴퓨터 저장소 내에 세팅을 합니다.

이후 SVN을 사용하여 Content(에셋 폴더)를 체크아웃하여 다운로드 합니다.


***주의, github에서 내려받은 Source 폴더와 SVN에서 받은***

***Contents, Config등등의 파일은 모두 한 폴더 안에 다같이 있어야 합니다.)***

-----------------------------------------------------------

### 5. SVN 파일 다운로드

Github 프로젝트 클론 폴더에서 SVN 서버주소를 입력 후

다운 받아 .uproject 파일을 우클릭하여 "Generate Visual Studio Project Files"를 실행합니다.

-----------------------------------------------------------

### 6. 에디터 실행
이후 해당 프로젝트 파일의 .sln 파일을 눌러 비주얼 스튜디오를 실행시키고

프로젝트를 빌드 하여 언리얼 엔진 에디터를 실행시킵니다.

-----------------------------------------------------------

# 에디터 뷰포트에서 쉐도우 그래픽 이슈 발생시

### 프로젝트 첫 실행시 프로젝트 내부 뷰포트에서 렌더링된 그림자의 모습이 비정상적으로 보일 것입니다.

이는 언리얼 엔진의 Lightmass 프로젝트가 제대로 컴파일 되지 않았기 때문입니다.

(또는 Lightmass의 실행파일이 최신버전이 아니라고 뜹니다) 때문에 꼭 UE5.sln파일(언리얼 엔진 Github)을 비주얼 스튜디오로 열어서

**솔루션 탐색기에서 UnrealLightmass 프로젝트 파일을 꼭 한번은 빌드를 하여야 합니다.**

현재까지 발견된 이슈들은 모두 프로젝트 세팅 변경으로 처리하여 

금일(*24.05.29) 기준으로 엔진상으로는 문제가 되는 버그 및 이슈는 현재는 없습니다.
