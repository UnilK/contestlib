"contestlib shortcuts 
map mk :silent !echo %<Bar>sed -r "s/(.+)\/(.+)\.cpp/-d \1 \2/"<Bar>xargs ./scripts/compile<CR><C-l>
map ml :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/run<CR><C-l>
map mj :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/debug<CR><C-l>
map nk :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/writetest<CR><C-l>
map nl :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/runtest<CR><C-l>
map ms :!./scripts/save<Space>

