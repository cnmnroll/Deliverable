#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;
//idx = player番号 reversecard = リバース判定 color = 記号変更カードの指定された記号 drawcard = ドロー系カード判定  recount = ドロー系カードが難解でたか
int idx = 0,reversecard = 0, color, drawcard = 0, recount = 0, drawjudge = 0;

//トランプ変換
struct Card{
    int number;
    int symbol;
};
//Playerの手札
struct Player{
    vector<Card> tehuda;
    int seiseki[15] = {0};
};

Player players[4]; //Player1〜3(使用:0,1,2)(3は確認用)
Player field; //フィールドカード

//カードデック作成
void create_carddeck(vector<int> &carddeck);
//ランダムシャッフルランダム化
unsigned int Random (unsigned int);
//ドロー
void draw(Player &players, vector<int> &carddeck);
//手札出力
void print_struct(Player, const string [] , const string []);
//手札・フィールド出力
void print_fieldtehuda(Player &, Player &, const string [], const string []);
//アクション(カードを出すか、出さないか)
int action_judge(Player);
//カード出す判定
int put_judge(Player, Player, int, int);
//カードを出す
void put_action(Player [], Player &, vector<int> &, vector<int> &, const string [], const string [], int);
//カードの役判定(ドローツー、スキップなど)
void card_judge(Player &, Player &, int);
//player変更
void r_judge();
//出力メッセージ
void message(Player, Player, const string [], const string [], int);
//カード並び替え
bool tfsort(const Card &left, const Card &right);
//手札スコア変換
int pscore(Player, int);
//中間結果
void midle_message(Player[], int, int, int);
//最終結果
void last_message(Player[], int , int);
//void carddeck_message(vector<int> carddeck);

int main() {
    int n, i, k, p, cardidx = 0, nots, tehuda,playcount = 0,idxkeep,carddecksize;
    string number[14] = {"0","2(ドロツー)","3(ドロスリー)","4","5","6","7","8","9(リバース)","10","J","Q","K","A(スキップ)"}; //トランプの数字
    string symbol[4] = {"SPADE", "HEART", "DIA", "CLUB"}; //トランプの記号
    vector<int> carddeck; //カードデック
    vector<int> carddeck2;
    
    while(1){
        printf("ゲーム回数を入力してください(1〜5):"); fflush(stdout);
        scanf("%d", &playcount);
        if(playcount <= 5){
            if(1 <= playcount){
                break;
            }
        }
        puts("1から5を入力してくだい。");
    }
    //ゲームスタート
    for(p = 0; p < playcount; p++){ //入力された回数ゲームを行う
        //カードデック作成
        create_carddeck(carddeck);
        
        //カードデック確認
        //for(i = 0; i < 52; i++) draw(players[4], carddeck); print_struct(players[4], number, symbol);
        
        //ランダム化
        random_shuffle(carddeck.begin(), carddeck.end(), Random);
        random_shuffle(carddeck.begin(), carddeck.end(), Random);
        //カードデックランダム後確認
        //for(i = 0; i < 52; i++) draw(players[4], carddeck); print_struct(players[4], number, symbol);
        
        //カードを引く
        for(i = 0; i < 3; i++){ //プレイヤーidx
            for(k = 0; k < 5; k++){
                draw(players[i], carddeck);
                //print_struct(players[i], number, symbol);
            }
        }
        
        //フィールド作成
        field.tehuda.push_back((Card){carddeck.back() % 14, carddeck.back() / 14});
        carddeck.pop_back();
        
        while(1){
            idxkeep = idx;
            //手札・フィールド出力
            if(idx == 0){
                print_fieldtehuda(players[idx], field, number, symbol); fflush(stdout);
            }
            while(1){
                if(idx != 0){ //自分以外
                    //printf("ppppppppppppppppppppppppppppppppppppppp\n");
                    tehuda = players[idx].tehuda.size();
                    //printf("%dqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\n", tehuda);
                    for(i = 0; i < tehuda; i++){
                        if(put_judge(players[idx], field, i, drawcard)){ //カードを出せるか出せないか判定
                            card_judge(players[idx], field, i); //カードの役判定
                            put_action(players, field, carddeck, carddeck2, number, symbol, i); //カードを出す
                            message(players[idx], field, number, symbol, field.tehuda[0].number); //動作終了ごのメッセージ
                            break;
                        }
                        //printf("%d\n", i);
                    }
                    if(i != tehuda) break;
                    if(drawcard != 0){ //ドロー系カードの時
                        nots = drawcard * recount; //ドローカード引く枚数
                        //カードを引くアクション
                        for(i = 0; i < nots; i++){ //nots分カードを引く
                            draw(players[idx], carddeck);
                        }
                        message(players[idx], field, number, symbol, -2); //動作終了ごのメッセージ
                        recount = 0; //ドロー回数解除
                        drawcard = 0; //ドローカード解除
                        break;
                    } else {
                        if(drawjudge == 0){ //一回目はカードを引く
                            draw(players[idx], carddeck); //カードを引く
                            //message(field, number, symbol, -1); //動作終了ごのメッセージ(カードを引きました)
                            //print_fieldtehuda(players[idx], field, number, symbol); //手札出力
                            drawjudge = 1; //カードを引いた証明
                        } else { //2回目は繰り返しを抜け次のプレイヤーへ
                            message(players[idx], field, number, symbol, 0); //動作終了ごのメッセージ (何も出しませんでした)
                            //printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
                            break;
                        }
                    }
                } else { //自分
                    //カードを出すか、カードを引くか
                    cardidx = action_judge(players[idx]);
                    if(cardidx == -1){ //カードを引くアクション
                        if(drawcard != 0){ //ドロー系カードの時
                            nots = drawcard * recount; //ドローカード引く枚数
                            //カードを引くアクション
                            for(i = 0; i < nots; i++){ //nots分カードを引く
                                draw(players[idx], carddeck);
                            }
                            message(players[idx], field, number, symbol, -2); //動作終了ごのメッセージ
                            recount = 0; drawcard = 0;
                            break;
                        } else { //それ以外
                            if(drawjudge == 0){ //一回目はカードを引く
                                draw(players[idx], carddeck); //カードを引く
                                message(players[idx], field, number, symbol, -1); //動作終了ごのメッセージ(カードを引きました)
                                print_fieldtehuda(players[idx], field, number, symbol); //手札出力
                                drawjudge = 1; //カードを引いた証明
                            } else { //2回目は繰り返しを抜け次のプレイヤーへ
                                message(players[idx], field, number, symbol, 0); //動作終了ごのメッセージ (何も出しませんでした)
                                break;
                            }
                        }
                    } else { //カードを出すアクション
                        if(put_judge(players[idx], field, cardidx, drawcard)){ //カードを出せるか出せないか判定
                            card_judge(players[idx], field, cardidx); //カードの役判定
                            put_action(players, field, carddeck, carddeck2, number, symbol, cardidx); //カードを出す
                            message(players[idx], field, number, symbol, field.tehuda[0].number); //動作終了ごのメッセージ
                            break;
                        }
                    }
                }
            }
            //ドローカウントリセット
            drawjudge = 0;
            //勝利判定
            if(players[idxkeep].tehuda.empty()){ //手札が0になったら勝利
                printf("%d回目\n!!!!!!!!!!!!!!player%dの勝利!!!!!!!!!!!!!!\n\n", p + 1, idxkeep + 1);
                for(i = 0; i< 40; i++) printf("-");puts("");
                break;
            }
            if(carddeck.empty()){ //カードデックが0になったら
                carddecksize = carddeck2.size();
                for(i = 0; i < carddecksize; i++){
                    carddeck.push_back(carddeck2[i]); //カードデックに場に出したカードを戻す
                }
                carddeck2.clear(); //カードデック2初期化
            }
            //次のプレイヤーへ
            r_judge();
            
        }
        
        midle_message(players, playcount, p, idxkeep); //中間結果
        carddeck.clear();
        idx = 0; drawcard = 0;
    }
    last_message(players, playcount, p); //総合結果
    return 0;
}

void create_carddeck(vector<int> &carddeck){
    int i;
    for(i = 1; i < 56; i++){
        if(i % 14 == 0){ //14で割り切る事ができる場合飛ばす(割った値、余りでカードを表現するため)
            continue;
        } else {
            carddeck.push_back(i);
            //printf("|%s %s|", number[carddeck.back() % 14].c_str(), symbol[carddeck.back() / 14]);
        }
    }
}

unsigned int Random (unsigned int max) {
    srand ((unsigned)time(NULL));
    return rand() % max;
}

void draw(Player &players, vector<int> &carddeck){
    int i;
    players.tehuda.push_back((Card){carddeck.back() % 14, carddeck.back() / 14}); //カードデックからカードを手札に引く
    //printf("%d %d\n", players.tehuda.back().number, players.tehuda.back().symbol);
    carddeck.pop_back(); //引いたカードをカードデックから削除
}

void print_struct(Player players, const string number[] , const string symbol[]) {
    int i;
    for(int i = 0; i < (int)players.tehuda.size(); i++) { //playersに入ってる枚数だけ出力
        printf("%d枚目 → %s %s %d", i+1,number[players.tehuda[i].number].c_str()
               , symbol[players.tehuda[i].symbol].c_str(), players.tehuda[i],number);
        printf(" %d\n", players.tehuda[i],symbol);
    } fflush(stdout);
}

void print_fieldtehuda(Player &players, Player &field, const string number[], const string symbol[]){
    printf("◆手札◆\n");
    sort(players.tehuda.begin(), players.tehuda.end(), tfsort);
    print_struct(players, number, symbol); //手札出力
    printf("\n☆フィールドカード☆\n");
    //フィールドカード出力
    printf("%s %s\n", number[field.tehuda[0].number].c_str(), symbol[field.tehuda[0].symbol].c_str());
    printf("player%dの番です\n", idx + 1);  fflush(stdout);
}

int action_judge(Player player){
    int action, test;
    test = player.tehuda.size();
    while(1){ //手札が無い場所を入力された場合再度入力
        printf("カードを出しますか(Yes:手札の場所,No:0):"); fflush(stdout);
        scanf("%d", &action);
        action -=1;
        if(action >= -1){
            if(test > action){
                break;
            }
        }
        puts("その手札は存在しません");
    }
    return action; //手札の場所+1の数or0を返す
}

int put_judge(Player players, Player field, int cardidx, int judge){
    if(judge != 0){ //ドロツー・スリー
        if(field.tehuda.back().number == players.tehuda[cardidx].number) return 1;
    } else { //それ以外
        //手札のナンバー=フィールドのナンバー、手札の記号=フィールドの記号、手札のナンバー=7(色変えカード)の時に1を返す。 それ以外は0を出力
        if(field.tehuda[0].number == players.tehuda[cardidx].number || field.tehuda[0].symbol == players.tehuda[cardidx].symbol || players.tehuda[cardidx].number == 7){
            return 1;
        }
    }
    if(idx == 0){
        puts("そのカードは出せません");
    }
    fflush(stdout);
    return 0;
}

void put_action(Player players[], Player &field, vector<int> &carddeck, vector<int> &carddeck2, const string number[], const string symbol[], int cardidx){
    if(players[idx].tehuda[cardidx].number == 7){ //記号変えカード(8)
        while(1){ //0-3の入力を拒否
            if(idx == 0){
                printf("どの記号に変えますか？(S:0,H:1,D:2,C:3):"); fflush(stdout);
                scanf("%d", &color);
            } else {
                color = Random(3);
            }
            if(color >= 0){
                if(4 > color){
                    break;
                }
            }
            puts("その記号はありません");
        }
        carddeck2.push_back(players[idx].tehuda[cardidx].number + players[idx].tehuda[cardidx].symbol * 14);
        field.tehuda[0] = (Card){players[idx].tehuda[cardidx].number, color}; //記号をcolorに変換してフィールドに手札を出す
        //手札減らす
        players[idx].tehuda.erase(players[idx].tehuda.begin() + cardidx); //手札から出したカードを消す
        color = 0;
    } else { //それ以外のカード
        carddeck2.push_back(players[idx].tehuda[cardidx].number + players[idx].tehuda[cardidx].symbol * 14);
        field.tehuda[0] = (Card){players[idx].tehuda[cardidx].number, players[idx].tehuda[cardidx].symbol}; //フィールドに手札を出す
        players[idx].tehuda.erase(players[idx].tehuda.begin() + cardidx); //手札から出したカードを消す
    }
}


void card_judge(Player &players, Player &field, int cardidx){
    if(players.tehuda[cardidx].number == 8){ //リバースカード(9)
        reversecard = (reversecard == 0) ? 1: 0;
    }
    if(players.tehuda[cardidx].number == 1){ //ドロツー(2)
        drawcard = 2;
        recount += 1;
    }
    if(players.tehuda[cardidx].number == 2){ //ドロスリー(3)
        drawcard = 3;
        recount += 1;
    }
}

void r_judge(){
    if(reversecard == 0){ //リバースカードが出されていない場合
        idx += 1; //player1→2→3
        if(idx == 3) idx = 0; //player1に戻す
    } else { //リバース状態
        idx -= 1; //player3→2→1
        if(idx == -1) idx = 2; //player3に戻す
    }
}

void message(Player player, Player field, const string number[], const string symbol[], int judge){
    int i, nots,pidx, pidx2;
    nots = drawcard * recount; //ドロツー、スリーの計算
    pidx = idx + 1;
    pidx2 = pidx;
    for(i = 0; i< 40; i++) printf("-");puts("");
    if(drawjudge != 0){ //自分以外かつどろーした場合
        if(idx != 0) printf("Player%dはカードを引きました\n", pidx);
    }
    if(judge == -1){
        printf("Player%dはカードを引きました\n", pidx);
    } else if(judge == 0) { //カードを出さない時(カードを引くとき)
        printf("Player%dはカードを出しませんでした\n", pidx);
    } else if(judge == -2){ //ドロー系を返せなかった時
        printf("Player%dはドロー%dを返すことができませんでした。\nPlayer%dの手札が%d増えました。\n", pidx, drawcard, pidx, nots);
    } else {
        printf("Player%dは[%s %s]を出しました。\n", idx + 1, number[field.tehuda[0].number].c_str(), symbol[field.tehuda[0].symbol].c_str());
        //ドロー系出した時
        if(judge == 1 || judge == 2) printf("%dカードです。ドロー%dを返してください。\n返さない場合%d枚カードが増えます。\n", drawcard, drawcard, nots);
        if(judge == 13){ //スキップカード
            r_judge(); //スキップ処理
            pidx2 = idx + 1; //player更新
            printf("スキップカードです。Player%dのターンがパスされます。\n", pidx2);
        }
        if(judge == 8) printf("リバースカードです。逆回りになります。\n"); //記号変え
    }
    
    if(idx != 0 || pidx != pidx2) printf("Player%dの手札は%d枚です\n", pidx, player.tehuda.size());
    for(i = 0; i< 40; i++)printf("-"); printf("\n"); fflush(stdout);
}

bool tfsort(const Card &left, const Card &right){
    if(left.number < right.number) return true;
    if(left.number > right.number) return false;
    return left.symbol > left.symbol;
}

int pscore(Player player, int k){
    int judge;
    judge = player.tehuda[k].number;
    if(judge == 9 ||judge == 10 || judge == 11 || judge == 11){
        return 10;
    } else if(judge == 1 || judge == 2 || judge == 7 || judge == 8 || judge == 12) {
        return 20;
    }
    return judge + 1;
}

void midle_message(Player players[], int playcount, int p, int idxkeep){
    int i, k, score;
    printf("%d回目結果\n", p + 1);
    for(i = 0; i < 3; i++){
        //if(i == idxkeep) continue;
        for(k = 0; k < (int)players[i].tehuda.size(); k++){
            score = pscore(players[i], k);
            players[i].seiseki[p] -= score;
            players[idxkeep].seiseki[p] += score;
        }
        
        players[i].tehuda.clear();
    }
    
    for(i = 0; i < 3; i++){
        printf("Player%d:%d点\n", i + 1, players[i].seiseki[p]); fflush(stdout);
    }
    for(i = 0; i< 40; i++) printf("-");puts("");
}

void last_message(Player players[], int playcount, int p){
    int i, k, max;
    int resultscore[5] = {0};
    printf("\n最終結果\n");
    for(i = 0; i < 3; i++){
        printf("player%d\n", i + 1);
        for(k = 0; k < playcount; k++){
            resultscore[i] += players[i].seiseki[k];
            printf("%d回目:%d点\n", k + 1, players[i].seiseki[k]);
        }
        if(i != 0){
            if(resultscore[max] < resultscore[i]){
                max = i;
            }
        } else {
            max = i;
        }
        
        printf("合計:%d点\n\n", resultscore[i]);
    }
    for(i = 0; i< 40; i++) printf("-");puts("");
    printf("!!!!!!!!!!!!!!Player%dの勝利!!!!!!!!!!!!!!\n", max + 1);
    for(i = 0; i< 40; i++) printf("-");puts("");
}

