" basic setup vim
set tabstop=8
set shiftwidth=8
set number relativenumber
set showmatch
set ignorecase
set autoindent
set smartindent
set wrap linebreak
set incsearch
set showbreak=...
syntax on

" spellcheck langs
set spelllang=en_us,pt_br

" autocommands
"au BufNewFile,BufRead *.tex setlocal spell
au BufNewFile,BufRead *.tex set textwidth=80
au BufNewFile,BufRead *.tex set tabstop=2 
au BufNewFile,BufRead *.tex set expandtab
au BufNewFile,BufRead *.tex set shiftwidth=2
au BufNewFile,BufRead *.txt set textwidth=80
au BufNewFile,BufRead *.md   set spell spelllang=en_us
au BufNewFile,BufRead *.html set textwidth=80
au BufNewFile,BufRead *.html set tabstop=2 
au BufNewFile,BufRead *.html set shiftwidth=2
au BufNewFile,BufRead *.css set textwidth=80
au BufNewFile,BufRead *.css set tabstop=2 
au BufNewFile,BufRead *.css set shiftwidth=2

" maps
map ; :wa<CR>
map t :wa \| !make<CR><CR>
map T :wa \| !make bibtex<CR><CR>
map m o<ESC>k
