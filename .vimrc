"contestlib shortcuts 
map mk :silent !echo %<Bar>sed -r "s/(.+)\/(.+)\.cpp/-d \1 \2/"<Bar>xargs ./scripts/compile<CR><C-l>
map ml :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/run<CR><C-l>
map mj :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/debug<CR><C-l>
map nk :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/writetest<CR><C-l>
map nl :silent !echo %<Bar>sed -r "s/.+\/(.+)\.cpp/\1/"<Bar>xargs ./scripts/runtest<CR><C-l>
map ms :!./scripts/save<Space>

function! s:Copypasta(copy)
    "somebody please tell me a way to get rid of all these backslashes, there has to be one.
    exec "silent !echo " . bufname("%")
                \ . "| sed -r \"s\/(.+)\\\/(.+)\\.cpp\/-d \\1 -p \\2\/\""
                \ . "| xargs ./scripts/load -c " . a:copy
    redraw!
    edit
endfunction

command! -nargs=1 Loadlib call s:Copypasta(<f-args>)

map ld :Loadlib ./lib/

