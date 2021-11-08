"compile
map mk :silent !echo %<Bar>sed -r "s/(.+)\/(.+)\..+/-d \1 \2/"<Bar>xargs ./scripts/compile<CR><C-l>

"compile for debugging
map mo :silent !echo %<Bar>sed -r "s/(.+)\/(.+)\..+/-d \1 -o \2/"<Bar>xargs ./scripts/compile<CR><C-l>

"run
map ml :silent !echo %<Bar>sed -r "s/.+\/(.+)\.(.+)/\1 -f \2/"<Bar>xargs ./scripts/run<CR><C-l>

"debug with gdb
map mj :silent !echo %<Bar>sed -r "s/.+\/(.+)\..+/\1/"<Bar>xargs ./scripts/debug<CR><C-l>

"write a test
map nk :silent !echo %<Bar>sed -r "s/.+\/(.+)\..+/\1/"<Bar>xargs ./scripts/writetest<CR><C-l>

"run the written test
map nl :silent !echo %<Bar>sed -r "s/.+\/(.+)\.(.+)/\1 -f \2/"<Bar>xargs ./scripts/runtest<CR><C-l>

"save task for upsolving. save <file name without extension> -m <message>
map ms :!./scripts/save<Space>

"append a file from lib to the cursor position
map ld :r lib/

