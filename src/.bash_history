exit
cd ../../mirage-www/
ls
cd src
ls
vim main.ml 
cd
rm -rf mirage-skeleton/

git clone git://github.com/mirage/mirage-skeleton.git
ls
cd mirage-skeleton/
ls
cd console/
ls
vim unikernel.ml 
vim config.ml 
ls
vim unikernel.ml 
cd ../..
ls
git clone git://github.com/mirage/mirage-www.git
ls
cd mirage-www/
ls
cd src/
ls
vim local_uri.ml 
vim pages.ml 
ls | xargs cat
ls | xargs cat | less
ls | xargs cat | wc -l
cd ../../mirage-skeleton/con
cd ../../mirage-skeleton/console/
ls | xargs cat | wc -l
sudo aptitude install xrdp
cd
cd mirage-skeleton/con
cd mirage-skeleton/console/
ls
make clean
ls
make distclean
vim Makefile 
ls
vim console_libvirt.xml 
vim main.ml 
vim unikernel.ml 
ls
screen
sudo aptitude install tmux
tmux 
sudo -s
su
opam --version
sudo
man sudo
ls
opam init
opam remote
ocaml -version
eval `opam config env`
opam list
opam install mirage
git clone git://github.com/mirage/mirage-skeleton.git
cd mirage-skeleton/
cd console/
mirage -version
mirage --version
mirage configure --unix
su
mirage configure --unix
make depend
make 
./mir-console 
egrep '(vmx|svm)' --color=always /proc/cpuinfo
apt-get install xen-linux-system xen-tools
sudo apt-get install xen-linux-system xen-tools
lsb_release -a
su
aptitude show xen-linux
aptitude show xen-linux-system
aptitude show xen-linux-system-amd64
ping 8.8.8.8
ifdown xenbr0
sudo ifdown xenbr0
ping 8.8.8.8
sudo service networking restart
sudo service networking stop
sudo service networking status
sudo service networking start
ping 8.8.8.8
ifconfig
sudo
sudo -s
mirage configure --xen
ls
ls -al
./console.xe 
make depend
make 
ls
ls -al
vim console.xl
xl
sudo aptitude install htop
sudo vim /etc/apt/sources.list
sudo -s
cd
git clone git://github.com/mirage/mirage-www
cd mirage-www/
ls
cd src/
env NET=socket PORT=8000 FS=crunch mirage configure --unix
make depend
make
make run
make urn
make run
cd ..
ls
cd src/
ls
cd _build/
ls
cd ..
env | less
history 
env NET=socket PORT=8080 FS=crunch mirage configure --unix
make depend
make
make run
ls
./mir-www 
ls
vim Makefile 
env NET=direct mirage configure --unix
make depend
make
sudo ./mir-www 
cd ../..
ls
rm -rf mirage-www/
sudo ifconfig tap0 10.0.0.1 255.255.255.0
sudo -s
ls
cd mirage-www/
ls
cd files/
ls
cd ..
ls
cd files/
ls
cd html/
ls
cd ..
ls
cd scripts/
ls
cd ..
ls
cd ..
ls
ls -al
vim TODO 
vim TROVE 
cd files/
ls
cd html/
ls
vim trace-viewer.html 
cd ../..
ls
cd ..
cd mirage-www/
ls
cd src/
ls
make 
make depend
make 
sudo ifconfig
sudo -s
ls
cd ..
ls
cd files/
cd ..
cd src/
ls
vim blog.ml 
vim template.ml 
cd
sudo service apache status
sudo service apache2 status
git clone http://xenbits.xen.org/mini-os.git
git://xenbits.xen.org/mini-os.git
git git://xenbits.xen.org/mini-os.git
git clone git://xenbits.xen.org/mini-os.git
ls
cd mini-os/
ls
cd include/
ls
cd ..
grep -rl boot
grep -rl pvboot
grep -rl 
grep -rl boot
cd ..
wget https://github.com/talex5/xen/archive/minios-v0.2.tar.gz
ls
tar zxvf minios-v0.2.tar.gz 
cd xen-minios-v0.2/
ls
cd extras/
ls
cd mini-os/
ls
grep -rl boot
grep -rl pvboot
vim arch/x86/mm.c 
grep -rl slab
grep -rl extent
vim mm.c 
ls
cd 
ls
cd Pictures/
ls
echo xfce4-session
echo xfce4-session > ~/.xsession
ls
ls -al
chmod 755 .xsession
vim .xsession-errors 
vim .xsession
ls
ls -al
vim .xsession
mv .xsession xession
sudo -s
vim .vnc/sesman_lilian_passwd 
vim .vnc/passwd
sudo -s
ssh bbsu@ptt.cc
locale -a
sudo -s
cd .config/ibus/
ls
mkdir rime
ibus
ibus list
cd .config/ibus/rime/
ls
vim default.yaml 
sudo -s
ls
cd Downloads/
ls
dpkg-deb help
dpkg-deb --help
dpkg-deb --help | less
aptitude --help
aptitude --help | less | grep install
dpkg -i google-chrome-stable_current_amd64.deb 
sudo dpkg -i google-chrome-stable_current_amd64.deb 
aptitude search google-chrome-stable
aptitude show google-chrome-stable
dpkg-deb -i 
dpkg-deb --info google-chrome-stable_current_amd64.deb 
rm -rf google-chrome-stable_current_amd64.deb 
sudo aptitude install google-chrome-stable
sudo -s
mail
rm /home/lilian/mbox 
ls
cd blog/
ls
php artisan config:cache
vim config/app.php 
php artisan config:cache
vim .env
mysql -u lilian -p
mysql -u lilian0111 -p
mysql -u lilian -p
mysql -u lilian0111 -p
mysql -u root -p
mysqladmin -u lilian -p
mysqladmin -u lilian -p password
mysql -u root -p
rm ~/.mysql_history 
mysql -u root -p
php artisan make:migration create_projects_and_tasks_tables --create="projects"
vim database/migrations/2015_06_05_034422_create_projects_and_tasks_tables.php 
php artisan migrate
vim config/database.php 
sudo aptitude install php-mysql
sudo aptitude install mysql-php
aptitude search php | less
aptitude install php5-mysql
sudo aptitude install php5-mysql
php artisan migrate
vim .env
mysql -u homestead -p
php artisan migrate
vim .env
mysql -u homestead -p
cd blog/
cd database/seeds/
ls
vim ProjectsTableSeeder.php
vim DatabaseSeeder.php 
vim TasksTableSeeder.php
composer dump-autoload
cd ../..
composer dump-autoload
php artisan db:seed
mysql -u homestead -p
php artisan db:seed
vim .env
aptitude show php5-mysql
aptitude search php | less
vim .env
php artisan db:seed
mysql -u homestead -p
php artisan migrate
php artisan config:clear
php artisan migrate
vim database/migrations/2015_06_05_034422_create_projects_and_tasks_tables.php 
php artisan migrate
php artisan db:seed
mysql -u homestead -p
php artisan make:model Project
php artisan make:model Task
php artisan  make:controller ProjectsController
php artisan  make:controller TasksController
vim app/Http/routes.php 
php artisan route:list
vim app/Http/routes.php 
php artisan route:list
vim app/Http/routes.php 
php artisan route:list
vim app/Http/routes.php 
php artisan route:list
exit
man readline
vim test.c
gcc test.c 
aptitude search readline | less
sudo aptitude install libreadline6-dev
gcc test.c 
vim test.c 
sudo aptitude install libreadline-dev
gcc test.c 
vim test.c 
sudo aptitude install libreadline5-dev
aptitude search readline | less
dpkg --get-selection
dpkg --get-selections
dpkg --get-selections | less
aptitude search readline | less
aptitude remove libreadline-de
sudo aptitude remove libreadline-dev
aptitude search readline | less
gcc test.c 
gcc test.c -lreadline
./a.out 
vim test.c 
man readline
./a.out 
man readline
vim test2.c
gcc test2.c -lreadline
./a.out 
vim test2.c 
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
./a.out 
gcc test2.c -lreadline
./a.out 
ls
./a.out 
vim /etc/inputrc 
vim /etc/in
vim /etc/inputrc 
./a.out 
bind TAB:menu-complete
exit
bind '"\C-i": menu-complete'
aptitude 
exit
bind '"\C-n": menu-complete'
exit
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
./a.out 
ls
vim test2.c 
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
.inputrc
vim .intputrc
vim /etc/inputrc 
vim test2.c 
aptitude search course | less
aptitude search curse | less
cd /etc/bash_completion.d/
l
ls
vim git-prompt 
vim apache2 
sudo -s
bash
vim /etc/inputrc 
sudo vim /etc/inputrc 
source /etc/inputrc 
vim /etc/inputrc 
sudo vim /etc/inputrc 
vim test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
vim /etc/inputrc 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
'
echo $PS3
PS3="****"
nano 
nano ps3.sh
chmod +x ps3.sh 
./ps3.sh 
man select
man 7 select
./ps3.sh 
echo PS3
echo $PS3
PS3=####
./ps3.sh 
PS3='####'
./ps3.sh 
vim ps3.sh 
./ps3.sh 
man select
vim test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim /etc/inputrc 
bind -p
bind -p | less
man bind
bash
vim /etc/inputrc 
ls
vim test2.c 
git config 
git clone https://github.com/orina1123/smartshell.git
ls
cd smartshell/
ls
vim README.md 
git add README.md 
git commit
git push
cd ..
ls
vim test2.c 
cp test2.c smartshell/
ls
cd smartshell/
ls
mkdir src
mv test2.c test.c
mv test.c src/
git add src
git add src/test.c 
git commit
git push
git clone git://git.debian.org/git/bash-completion/bash-completion.git
cd bash-completion/
ls
cd completions/
ls
vim gcc 
cd ..
git clone git://git.savannah.gnu.org/bash.git
cd bash
ls
grep -rl readline.h
aptitude grep completion .
aptitude grep -rl completion .
grep -rl completion
vim lib/readline/readline.c
vim lib/readline/complete.c 
grep -rl history .
grep -rl history . | less
grep -rl history.h . | less
vim lib/readline/examples/Inputrc 
vim lib/readline/examples/fileman.c 
vim lib/readline/examples/rltest.c 
vim lib/readline/examples/histexamp.c 
cd lib/readline/examples/
ls
gcc histexamp.c -lreadline
cd ../.../..
cd ../../..
ls
vim M
vim Makefile.in 
./configure 
ls
make
ls
cd tests/
ls
ls -al
cd ..
ls
cd lib/readline/examples/
ls
./a.out 
rm a.out 
cd ..
ls
vim Makefile
cd lib/
ls
cd readline/
ls
cd doc/
ls
vim Makefile 
cd ..
ls
cd ..
ls
vim README 
vim Makefile
cd lib/
ls
cd readline/
ls
cd examples/
ls
make
ls
vim histexamp.c 
vim Makefile 
make
make clean
vim Makefile 
make all
make hisexamp
vim Makefile 
make
./histexamp 
vim histexamp.c 
./histexamp 
vim histexamp.c 
ls
vim history_file 
rm history_file 
vim histexamp.c 
ls ~/.bash_history 
vim histexamp
vim histexamp.c 
make
./histexamp 
vim histexamp.c 
make
./histexamp 
ls
vim history_file 
vim histexamp
vim histexamp.c 
cd
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
history 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
./a.out 
gcc test2.c -lreadline
./a.out 
vim test2.c 
history  | less
vim test2.c 
history  | less
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
vim .bash_history 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim bash/lib/readline/examples/histexamp.c 
ls
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
./a.out 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
./a.out 
vim test2.c 
./a.out 
vim test2.c 
./a.out 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
gcc test2.c -lreadline
./a.out 
vim test2.c 
history  | less
vim .bash_history 
ls
cd bash
ls
./bashversion 
./bashbug 
ls
grep -rl complet . | less
cd examples/
ls
vim INDEX.txt 
cd complete/
ls
vim complete-examples 
vim bash_completion 
cd ..
grep -rl completion . | less
vim lib/readline/examples/fileman.c 
grep -rl main .
grep -rl main . | less
cd examples/loadables/
ls
vim README 
vim mkdir.c 
vim cat.c 
cd ..
ls
vim INDEX.txt 
vim startup-files/
cd misc/
ls
cd ..
ls
cd ..
grep -rl menu-complete
grep -rl menu-complete .
grep -rl main( . | less
grep -rl main\( . | less
grep -rl exe_cmd | less
grep -rl execute_cmd | less
vim bashline.c 
vim execute_cmd.c 
cd ..
ls
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vi test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
cd bash/lib/readline/examples/
ls
vim fileman.c 
cd
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
./a.out 
vim test2.c 
cd bash/lib/readline/
ls
vim complete.c 
vim ~/test2.c 
grep -rl rl_attempted_completion_function .
vim complete.c 
cd examples/
ls
./fileman 
vim fileman.c 
ls
vim rltest.c 
vim rlcat.c 
vim rl.c 
vim excallback.c 
vim rl-callbacktest.c 
cd
grep -rl rl_message .
grep -rl rl_message bash
vim bash/lib/readline/examples/rl
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
man rl_insert_text
grep -rl rl_insert_text .
grep -rl rl_insert_text bash
grep -rl rl_insert_text bash | grep *.c
grep -rl rl_insert_text bash | grep .c
grep -rl rl_insert_text bash | grep c$
vim bash/lib/readline/complete.c 
vim test2.c 
grep -rl rl_completion_display_matches_hook bash
vim bash/lib/readline/complete.c
aptitude search libreadline | less
cd bash
ls
cd ..
ls
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c .
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
gcc -lreadline test2.c 
vim test.c 
vim test2.c 
man readline
man bash
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
vim test.c 
rm test.c 
vim test2.c 
ls
cp test2.c smartshell/src/
cd smartshell/src/
git add test2.c
cd ..
git commit
git push
git pull
git merge
git status 
git push
cd 
ls
vim test2.c 
gcc -lreadline test2.c 
vim test2.c 
gcc -lreadline test2.c 
./a.out 
cp test2.c smartshell/src/test2.c 
cd smartshell/src/
git add test2.c 
cd ..
git pull
git commit
git push
exit
