#include <iostream>
using namespace std;

int peek_t, peek_h;
int total = 0;
int dif_t, dif_h;

void change_t(){
    peek_t += (dif_t / 10) * 10;
    peek_h -= dif_t / 10;
    if(peek_h < 0) peek_h = 0;
    
    total += (dif_t / 10) * 10;
}

void change_h(){
    peek_h += (dif_h / 10) * 10;
    peek_t -= dif_h / 10;
    if(peek_t < 0) peek_t = 0;
    
    total += (dif_h / 10) * 10;
}

int main(){
    int X; int Y;
    cin >> X >> Y;
    
    //최소화 할 수 있는 방법 현재 상태가 0일때 최대한 많이 penalty를 벌어야 함.
    //컴파일용
    int cnt = 0;
    
    dif_t = X - peek_t;
    dif_h = Y - peek_h;

    while(1) {
        cnt++;
        //계산
        if(dif_t < 10 && dif_h < 10){ //종료 조건
            total += (dif_t + dif_h);
            X = peek_t;
            Y = peek_h;
            break;
        }
        else if(dif_t < 10){
            change_h();
        }
        else if(dif_h < 10){
            change_t();
        }
        else {
            if(peek_h - dif_t/10 < 0 && peek_t - dif_h/10 < 0){
                if(peek_h - dif_t/10 < peek_t - dif_h/10){ //dif_t > dif_h
                    change_t();
                }
                else{
                    change_h();
                }
            }
            else if (peek_h - dif_t/10 < 0) {
                change_t();
            }
            else if(peek_h - dif_t/10 < 0){
                change_h();
            }
            else {
                change_t();
                change_h();
            }
        }
        
        dif_t = X - peek_t;
        dif_h = Y - peek_h;
    }
    
    cout << total << '\n';
}

/* 이걸 일반화함
 if(X > Y){
     Y += X / 10;
     total_t = Y * 10;
     X %= 10;
 }
 else{
     X += Y / 10;
     total_h = X * 10;
     Y %= 10;
 }
 */


/*20438
int N, K, Q, M;
int sleep[5001]; int code[5001];

int check(int first, int last){
    int result = 0;
    
    for(int i = first; i <= last; i++){ //i <- 입장 번호
        //순서 중요
        //조건1) 졸지 않으면 조건2도 탐색, 졸고 있으면 더 이상 탐색하지 않고 i 증가
        bool flag = true;
        for(int j = 0; j < K; j++){
            if(i == sleep[j]) { flag = false; break; }
        }
        if(!flag) continue;
        //의도: 첫번째 for문은 탈출하고 두번째 for문은 continue하고싶다
        //위의 의도를 더 쉽게 짤 수 있는 방법이 있지 않을까?
        
        //조건2) code[]의 배수가 아닐 때 체크
        for(int j = 0; j < Q; j++){
            if(i % code[j] == 0){ //배수이다. result++
                result++;
                break;
            }
        }
    }
    
    return result;
}

int main(){
    cin >> N >> K >> Q >> M;
    
    //졸고 있는 사람
    for(int i = 0; i < K; i++){
        cin >> sleep[i];
    }
    //출석 코드 받은 사람
    for(int i = 0; i < Q; i++){
        cin >> code[i];
    }
    
    for(int re = 0; re < M; re++) { //구간별 출석체크한 사람 체크
        int idx_f, idx_l;
        cin >> idx_f >> idx_l;
        
        cout << N - check(idx_f, idx_l) << '\n';
    }
}
 */

