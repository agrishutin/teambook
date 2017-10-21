set nocompatible
syntax on

set autoindent smartindent expandtab shiftwidth=4 tabstop=4 softtabstop=4 smarttab

set hlsearch incsearch
set gdefault " replace with g flag

" backups {{{
    set backup backupdir=~/.vim/backupdir
    if has('persistent_undo')
        set undodir=~/.vim/undodir undofile
        set undolevels=1000            " Maximum number of changes that can be undone
        set undoreload=10000        " Maximum number lines to save for undo on a buffer reload
    endif
" }}}

" Position restore {{{
    " Instead of reverting the cursor to the last position in the buffer, we
    " set it to the first line when editing a git commit message

    autocmd BufReadPost * if line("'\"") > 0 && line ("'\"") <= line("$") | exe "normal! g'\"" | endif
" }}}

autocmd FileType make setlocal noexpandtab

map <F8> :cope<Enter>:cc<Enter>
map <S-F8> :cclo<Enter>
map <F9> :cn<Enter>
map <S-F9> :cp<Enter>

map <F10> :make<Enter>
