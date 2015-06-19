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
arg1 吃 char\*, 

arg2 同 rl\_bind\_key
