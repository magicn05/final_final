## 1. 프로젝트명
      나의 첫 게시판

## 2. 프로젝트 설명
      TCP/IP 를 이용한 게시판, 자료실, 채팅방 (C++, C를 곁들인)

## 3. 프로젝트 설치 및 실행방법
      1. 저장된 소스를 로컬 컴퓨터에 clone 한다. (ssh : 
      2. clone 된 폴더에 들어가서 make clean 명령어로 혹시나 불필요한 파일이 있을수도 있으니 제거한다.
      3. make 를 해서 실행파일을 만들어준다.
      4. ~ 폴더로 들어가서 ./server 명령어로 서버 프로그램을 실행한다.
      5. ~ 폴더로 들어가서 ./client 127.0.0.1 클라이언트 프로그램을 실행한다.

## 4. 프로젝트 사용 방법
      1. 로그인 아이디를 입력해서 프로그램에 로그인 한다.
         -> 로그인 아이디가 없으면 회원가입을 통해 로그인 한다.
      2. 
## 5. 참고자료
      1. https://www.boost.org/users/download/


Boost 라이브러리 설치 필요
설치 방법
1. sudo apt-get update
2. https://www.boost.org/users/download/
3. boost_1_80_0.tar.gz 다운로드
4. home/mobis 에 압축파일 저장후 압축 해제 (tar -xvf boost_1_80_0.tar.gz)
5. 해당 폴더로 들어간후
6. ./bootstrap.sh
7. sudo ./b2 install
