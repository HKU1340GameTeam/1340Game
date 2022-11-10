
call plug#begin('~/.vim/plugged')
"Plug 'https://github.com/Zarainia/vim-scrollbar'
Plug 'terryma/vim-multiple-cursors'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'preservim/nerdcommenter'
Plug 'preservim/nerdtree'
Plug 'https://github.com/farmergreg/vim-lastplace'
Plug 'wesQ3/vim-windowswap'
" Plug 'vimwiki/vimwiki'
" Use release branch (recommend)
" Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

" gruvbox
set background=dark

" allow mouse scrolling to work
:set mouse=a


set number
set relativenumber
set backspace=indent,eol,start
set nocompatible
filetype plugin on

" configure expanding of tabs for various file types
au BufRead,BufNewFile *.py set expandtab
au BufRead,BufNewFile *.c set noexpandtab
au BufRead,BufNewFile *.cpp set noexpandtab
au BufRead,BufNewFile *.h set noexpandtab
au BufRead,BufNewFile Makefile* set noexpandtab

" --------------------------------------------------------------------------------
" configure editor with tabs and nice stuff...
" --------------------------------------------------------------------------------
set expandtab           " enter spaces when tab is pressed
set textwidth=120       " break lines when line length increases
set tabstop=4           " use 4 spaces to represent tab
set softtabstop=4
set shiftwidth=4        " number of spaces to use for auto indent
set autoindent          " copy indent from current line when starting a new line
set smartindent
set smarttab
set expandtab
set number

" make backspaces more powerfull
set backspace=indent,eol,start

set ruler                           " show line and column number
syntax on               " syntax highlighting
set showcmd             " show (partial) command in status line


" config for code folding
autocmd BufWrite * mkview
autocmd BufWinLeave * mkview
autocmd BufRead * silent loadview


" config for NERD Tree
" Start NERDTree and put the cursor back in the other window.
" autocmd VimEnter * NERDTree | wincmd p

" config for last place
 let g:lastplace_open_folds = 0

:map \RR :! python %<CR>
:map \CC :! g++ -pedantic-errors -std=c++11 % -o %:r<CR>
:map \RC :!./%:r<CR>
:map \CS :!chmod u+x %<CR>
:map \RS :!./%<CR>
:map \FF A{}<LEFT><CR><ESC>O
:map \Cpp :r !date<ESC>i// <ESC>kddo<BS><BS><BS>#include<iostream><CR>#include<string><CR>using namespace std;<CR><CR>int main()<ESC>FF <BS>return 0;<ESC>O
"<ESC>O// beginning of main<CR><BS><BS><BS>
map <C-c> "+y<CR>

set ic
