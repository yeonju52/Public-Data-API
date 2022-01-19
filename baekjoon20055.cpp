#include <iostream>
using namespace std;
#define QMAX 210 //2n = 200-1
#define CNTMAX 200001 //i번째 단계의 최대(대충 계산): 200 * 1000

int main() {
    //입력
    int N; cin >> N;
    int k; cin >> k;

    int que[QMAX]; // 벨트의 내구성 값 - 위치 저장
    for (int i = 0; i < 2 * N; i++) {
        cin >> que[i];
    }

    //변수
    int robotPosition[CNTMAX]; //배열의 value => 로봇의 위치
    int numRobot = 0; //로봇의 개수
    int startR = 0; //robotPosition의 첫번째 idx, 로봇 제거시 startR 1씩 증가
    int zeroDurable = 0; //내구성이 0인 칸의 개수
    int cnt = 0; //출력: cnt번째 단계

    //계산
    int dropPos = cnt % (2 * N); //cnt번째 단계에서 로봇을 내리는 위치
    int raisePos = dropPos + (N - 1); //cnt번째 단계에서 로봇을 올리는 위치
    for (; cnt <= CNTMAX;) {
        cnt++;
        //1번) 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
        //cnt번째의 내리는 위치, 올리는 위치
        dropPos = ((dropPos - 1) + 2 * N) % (2 * N); // cnt증가할 때마다(cnt번째 단계) dropPos 1씩 감소 ////위치 계산 중 음수가 나오면 + (2 * N)이 필요함
        raisePos = (dropPos + (N - 1)) % (2 * N);
        //로봇이 "올리는 위치"에 있다면, 로봇 제거
        int idx = startR;
        for (; idx < numRobot; idx++) {
            if (raisePos == robotPosition[idx]) { //로봇 제거
                startR++; //로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며 = 뒤에 있는 로봇이 앞에 있는 로봇을 역전할 수 없다.
                break;
            }
        }

        //2번) 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
        //다만, 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며(뒤에 있는 로봇이 앞에 있는 로봇을 역전할 수 없다.), 그 칸의 내구도가 1 이상 남아 있어야 한다.
        idx = startR; //idx 초기화
        for (; idx < numRobot; idx++) {
            bool flag = true; //idx번째 로봇이 이동할 수 있는가?
            int movePos = (robotPosition[idx] + 1) % (2 * N); //한 칸 이동할 때의 위치
            if (que[movePos] > 0) { //내구도 1 이상인지 확인
                for (int j = startR; j < numRobot; j++) {
                    if (idx != j && movePos == robotPosition[j]) { flag = false; break; }
                }

                if (flag) { //idx번째 로봇이 이동할 수 있다면,
                    //1) 로봇 배열의 값(로봇의 위치) 1 증가
                    robotPosition[idx] = movePos;
                    //2) 올려진 위치 내구도 감소
                    que[movePos]--;
                    if (que[movePos] == 0) { //내구도 0이 되었는가?
                        zeroDurable++;
                    }
                    //3) 로봇이 "올리는 위치"에 있다면, 로봇 제거
                    if (raisePos == movePos) { //로봇 제거
                        startR++; //로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며 = 뒤에 있는 로봇이 앞에 있는 로봇을 역전할 수 없다.
                    }
                }
            }
        }


        //3번) 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
        if (que[dropPos] > 0) {
            //1) 로봇을 벨트에 내림
            robotPosition[numRobot++] = dropPos; //로봇의 개수: numRobot
            //2) 올려진 위치 내구도 감소
            que[dropPos]--;
            if (que[dropPos] == 0) { //내구도 0이 되었는가?
                zeroDurable++;
            }
        }

        //4번) 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
        if (zeroDurable >= k) { break; }
    }


    //출력
    cout << cnt << endl;

    ////출력(디버깅용)
    //for (int i = 0; i < 2 * N; i++) {
    //    cout << que[(cnt + i) % (2 * N)] << " ";
    //}
    //(cnt + 처음 벨트 index) % 2n (circularQueue라서 2n의 나머지 계산)
}
