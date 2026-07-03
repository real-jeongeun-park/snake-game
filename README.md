# 🐍 Snake Game

2022학년도 2학기 C프로그래밍 학기말 프로젝트로 구현한 C언어 기반 Snake Game입니다.<br/>
고전 게임 Snake에서 아이디어를 얻어 제작했으며, 기존의 일부 기능은 제거하고 새로운 기능(Vitality, Time Checking 등)을 추가해 재구성했습니다.

## 📌 게임 소개

플레이어는 방향키로 Snake를 조작해 **최대한 오랫동안 생존**하는 것이 목표인 게임입니다.

- 시간이 지날수록 Snake의 Vitality(생명력)이 점차 감소합니다.
- 화면에 랜덤으로 생성되는 Medicine(+로 표시)을 먹으면 Vitality를 회복할 수 있습니다.
- Vitality가 0이 되거나, Snake가 게임 필드(벽) 밖으로 벗어나면 게임이 즉시 종료됩니다.
- 생존 시간이 곧 **Score**이며, 플레이 시간이 길어질수록 Vitality 감소 속도가 점점 빨라져 난이도가 상승합니다.
- 최고 기록(Highest Score)은 파일에 저장되어 다음 플레이에도 유지됩니다.

## 🛠 사용 기술 / 개발 환경

- **언어**: C
- **개발 환경**: Visual Studio 2022 (Windows)
- **사용 헤더 파일**
  - `<stdio.h>` — 표준 입출력, 최고 점수 파일 저장/불러오기 (`fopen`, `fprintf`, `fscanf`)
  - `<stdlib.h>` — 난수 생성(`rand`), 콘솔 초기화(`system("cls")`)
  - `<conio.h>` — 콘솔 키 입력 감지 (`kbhit`, `getch`)
  - `<time.h>` — 경과 시간 계산 (`clock`)
  - `<windows.h>` — Windows API (`Sleep`, 커서 위치 제어 등)

## 🎮 조작 방법

| 키 | 동작 |
|---|---|
| ↑ / ↓ / ← / → | Snake 이동 방향 전환 |
| 1 | 게임 시작 |
| 2 | 도움말(게임 설명) 보기 |

> 이동 중인 방향의 반대 방향키는 입력이 무시됩니다. (예: 오른쪽으로 이동 중일 때 왼쪽 키 입력 불가)

## 🖥 화면 구성

프로그램은 `gameStatus` 값에 따라 총 4가지 화면으로 전환됩니다.

1. **시작 화면** (`gameStatus == 0`) — 게임 제목 표시, 시작/도움말 선택
2. **도움말 화면** (`gameStatus == 2`) — 게임 규칙 및 설명
3. **게임 화면** (`gameStatus == 1`) — Snake 이동, Vitality/점수 표시
4. **종료 화면** (`gameStatus == 3`) — 최종 점수 및 최고 기록 표시

<img width="1364" height="1232" alt="콘솔창" src="https://github.com/user-attachments/assets/8dc852b0-d0cb-4d01-ab55-b3ad736ff1f5" />

## 🔀 순서도

<img width="1364" height="1688" alt="기능 copy" src="https://github.com/user-attachments/assets/1c9bc8b6-e051-4b13-a9fc-a86d5b7c8663" />

## ✨ 주요 기능

- Snake 및 게임 필드(맵) 렌더링
- 방향키 입력 처리 및 이동 로직
- 랜덤 위치에 Medicine 생성
- 경과 시간(Score) 계산
- 플레이 시간에 따른 난이도(Vitality 감소 속도) 자동 조절
- 최고 점수 파일 저장 및 불러오기 (`highscore.txt`)

## 📁 참고

자세한 설계 과정, 순서도, 구현 코드 및 결과 분석은 프로젝트 리포트(`report.pdf`)를 참고해 주세요.
