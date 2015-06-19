想到什麼記什麼...

####rl\_bind\_key(arg1, arg2)
arg1 是選擇要 bind 的 key, 因為他吃 char 所以這個 function 是一個鍵的 bind  
有些 key library 已經有 macro 了, 可以直接用不用丟 ascii 碼  
DEL, ESC, ESCAPE, LFD, NEWLINE, RET, RETURN, RUBOUT, SPACE, SPC, and TAB  
[ref link](https://cnswww.cns.cwru.edu/php/chet/readline/readline.html)  
原本我要試用 ESC, 不過用了 ESC 後往上 (arrow up) 就會壞掉  

arg2 是打了這個鍵後要跳進去執行的 function  
function prototype:  
int func (int count, int key)  
這個 function 的第二個參數 key 是原本那個按鍵的 ascii, 有時後有很多 key bind 到同一個 function,
可以用這個來辨認是按了哪個 key 才 call 這個 function

####rl\_bind\_keyseq(arg1, arg2)
arg1 也是選擇要 bind 的 key, 他可以選擇 esc-a, ctrl-c, meta-c 等等的組合 key  
(註: meta key 通常是鍵盤左邊的 alt)  
arg1 吃 char\*, 本來就有定義好的一些組合 key 組合直接丟就好  
例如說 "\\\\C-k" 這個 string 就是 ctrl-k 這個組合鍵了

arg2 同 rl\_bind\_key

#### 幾個常用的變數(?)
#####rl\_line\_buffer
存現在的prompt 裡面的文字們  
例如 --shell--> abc def ghi  
rl\_line\_buffer 就是 "abc def ghi"
這個變數歡迎隨便亂改, 只是亂改完不會馬上 apply 上去 (廢話...)

#####rl\_point
存現在的 cursor 在哪裡
例如
abc def ghi  
   ^  
   |  
cursor  
這個時候 rl\_point == 4  
(按: 是 3 還是 4 我忘了, 不確定 Orz)  
這個變數也是可以隨便亂改, 改了游標就換了喔  
原本的 Ctrl-a 就是把 cursor 移到最前面
簡單版的就是只要寫  
rl\_point = 0;  
應該就可以了  
只是好像有什麼 emacs\_mode 還有啥 vi\_mode 的 issue 等等(我沒研究), 所以 source code 應該不會就只有這樣一行啦XD"

#### 去 readline source code 裡面找範例...
光是只看 document page 根本就...我慧根不足吧, 找自己知道怎麼做的功能去 trace source code 會比較快
有些很底層的東西他都有寫好的 function 可以直接 call  
(ex, 砍掉現在 prompt 的字之類的, 找前一個字的 point)
source code 前面有底線的 function 只 include lib readline 應該沒有辦法用..., 如果要參考(抄)他的 code 可能需要多一點功夫

#### rl\_complete Orzzzzzzzz
範例程式上面寫的是這樣  
```C
rl_attempted_completion_function = my_completion;   // 把 completion func 改成自己寫的
...
bind_key('\t', rl_complete);   // bind 到原本的 rl_complete func
...
char ** my_completion( const char* text, int start, int end){
	...
	matches = rl_completion_matches ((char*)text, &my_generator);  // 自己生成的 match list 的來源找 my_generator
	...
}
```

source code (complete.c) 大概是  
按了 TAB 鍵去 call rl\_complete  
rl\_complete 裡面會去 call rl\_complete\_internal(what\_to\_do)  
rl\_complete 會依據不同的 completion 呈現形式丟不同的 what\_to\_do 參數
前面那個 \_rl\_insert 這樣寫是想要按兩次 TAB 才會出現 completion (大概吧, 我不確定)

幾個自己試的參數
#####'?'
在 prompt 下面列出 matches (可能可以補完的各種 command/filename)
#####TAB(ascii 27)
standard 補完, 他說的, 我也不知道 standard 是指啥鬼, 實際上測就是, 只補後面  
例如有 History.h, History.c 在 working dir  
prompt > vim His  
按了 tab  
prompt > vim History.  
只有這樣, 沒有下面的 list
#####'\*'
只補後面(像上面講的), 但是在 rl\_complete 沒有寫 rl\_complete\_internal('\*'); 之類的東西
#####'!' (大概是我們要的)
會 list 也會補 prompt line 上面的東西
#####'@'
按第一次 tab 補 prompt line  
之後再按 tab 就會印出下面的候選 list  

rl\_complete\_internal 會去 call
```C
matches = gen_completion_matches (text, start, end, our_func, found_quote, quote_char);
```
上一行是 source code 裡面寫的, our\_func 就是 completion function  
然後 gen\_completion\_matches 裡面會看 rl\_attempted\_completion\_function 是不是 0  
如果不是 0 (就是像範例程式那樣把他指定成 my\_completion 就不是了), 就會執行 rl\_attmpted\_completion\_function 裡面指定的 match function  
然後回傳 matches 結果  

rl\_completion\_internal 會依照拿到的 matches 看原本的參數 (?!@ 等等的) 是什麼再印出來  
如果要用他寫好的印出來的那些 function, 可能就無法插入數字什麼的  
因為他丟回去 rl\_line\_buffer 裡面的東西也是根據 matches  
還有印出來的東西也是根據 matches, 所以...可能要重抄一遍他的東西 (?)  

(按: matches[0] 和 matches[1] 後面的好像不太一樣, [0] 好像用於 rl\_line\_buffer 補完, [1] 用於之後的 list command/filename, 或許可以在 list 那邊塞就不會有問題也不用重寫了, 這個我還要再確認一下)  
