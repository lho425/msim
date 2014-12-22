#初期設定
cygwinを入れる
gccを入れる


下のチュートリアルを読む

あなたのコードをシミュレータで動くように移植する

main.c.template を コピーしてmain.cという名前に変える

main.cを適宜書き換える 

map.txtを編集

cygwinのコンソールで以下のコマンドを実行

./map2Ccode.sh map.txt mywalldata.c

gcc -O2 main.c msim.c mywalldata.c  -o msim

./msim.exe


#チュートリアル

##移植編
まず、あたなのマウスのプログラムをシミュレータ上で動くように修正(移植)しなくてはいけません。 
あたなは、センサの値を見たり、モーターに電圧をかけたりするために、マイコンを操作するコードを書いているはずです。 
このシミュレータ上ではそのような原始的なことはシミュレート出来ませんが、代わりに 
 - 自分の前に壁があるか調べる
 - 右を向く
 - 前に1マス進む

という操作ができる関数を用意しています。具体的には、上で書いた操作は

    int msim_existsWallAt(enum msim_Direction d);

    void msim_turnMouseTo(enum msim_Direction d);

    int msim_moveMouseToFront();

の3つの関数を通して行います。方向(マウスから見た前後左右)を指定するには

    enum msim_Direction { front, right, back, left }
を使います。

例えば、自分の右に壁があるか調べて、壁がなけれは右に進む、ということをするには

    if (msim_existsWallAt(right)){
        msim_turnMouseTo(right)
        msim_moveMouseToFront()
    }
という風にすればよいですが、あなたは、あなたが書いた壁判定関数や移動関数を、上で挙げた3つの関数を呼び出すように移植するべきです。そうすれば、あなたの迷路探索アルゴリズムを一切書き換えることなくシミュレータ上で動かせるでしょう！
msim_moveMouseToFront()は、移動時に壁に激突してしまった、もしくは既に壁に激突していた場合0を返しその場に留まり、壁に激突せずに移動できた場合1を返します。

##迷路表示編
迷路とあなたのマウスがどこにいるのかを見るときは

    void msim_printMap()
関数を呼びます。"<", ">", "A", "V" の記号で向きが表示されます。 
壁に激突した場合、たとえは東壁に激突した場合マウスは ">X>" という表示になります。

##実際にシミュレータを動かす編
迷路の壁情報を設定し、オプションを指定し、あなたの実行したい関数、例えば足立法でゴールまで行く、ような関数を実行します。基本的にはmsim.c(msim.c.templateをコピーして、msim.cにリネームしてください)に書いてあるのを書き換えればいいです。

##オプションの設定の仕方
    void msim_setOptions(int flags)
を使ってオプションを指定します。二回以上呼んだ場合、オプションは追加ではなくその都度リセットして設定されます。

    msim_setOptions(flag_draw_on_move | flag_draw_on_turn);
という感じで、論理和でオプションを指定します。
現在以下のオプションが指定できます:
 - flag_print_on_move
msim_moveMouseToFront関数が呼ばれたら msim_printMap関数を呼ぶ
 - flag_print_on_turn
msim_turnMouseTo関数が呼ばれたら msim_printMap関数を呼ぶ
 - flag_no_option
なんのオプションも指定しない。msim_setOptions(flag_no_option)とすればオプションはリセットされます。

将来もっとオプションが追加されるかも知れません。

#ライセンス
msimプロジェクトに属するすべてのファイルはパブリックドメインとします。

ファイルの先頭にその旨の断りがなかったとしても、パブリックドメインです。

#change log

2014/12/22
- gitレポジトリ作り直して一般公開
- ライセンスについてreadmeで明言 

2014/12/18 
- チュートリアル追加 
- 使い方が変更された 
- オプションが変更された(互換性のない変更) 

2014/11/7 
 - マウス視点の壁判定・移動関数を追加
  - msim_existsWallAt関数
  - msim_turnMouseTo関数
  - msim_moveMouseToFront関数
 - msim_moveMouseTo関数を廃止 
