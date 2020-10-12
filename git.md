## Git基本配置

Git --version 查看git版本号

Git config 配置或读取环境变量

 Git config --system user.name xxx

系统所有用户默认配置，无以下两个默认用这个，在/etc/gitconfig文件中查看

 Git config --global user.name xxx

本用户的默认配置，无以下一个默认用这个，在~/.gitconfig文件中查看

 Git config user.name xxx

当前项目git目录中默认配置，优先使用这个，在.git/config中查看

 常用需要配置的选项：

Git config --global user.name xxx	用户名      

Git config --global user.email xxx	用户邮件地址

Git config --global core.editor vim	系统默认编辑器

Git config --list		查看默认配置

## git基本操作

 Git init		在当前目录创建git仓库，生成.git目录

 Git status	查看当前目录的文件状态，包含：

 已提交到git仓库的

位于工作区未track（追踪）的

位于工作区已追踪待提交的

 Git add和git rm在git init命令中有介绍

 Git commit

Git commit	xxx 将已track待提交的文件提交，此命令会进vi编辑提交信息，

git commit -m”ooo” xxx其中-m”ooo”参数可以直接在””中输入提交信息，不用进入vi编辑器

 Git log	

 Git log完整显示版本信息

 Git log --pretty=oneline	简洁一点显示（放在一行显示）

 Git log --oneline	比上面更简洁显示（缩短了哈希值）

Git reflog	在oneline基础上多现实了到某一个版本需要几步，且能显示之前之后的所有版本（显示的最全）

 Git reset

Git reset --hard 824921c	跳转到缩短哈希值82..对应的版本

Git reset --hard HEAD^^		跳转到所在版本的上两个版本（取决于^个数）

Git reset --hard HEAD~2		等价于上面，直接用数值表示比用^个数表示方便

注：以上两个只能后退，第一个跳转可以往前可以往后

Git reset --hard xxx	仅仅在本地库移动HEAD指针

Git reset --mixed xxx 移动本地库HEAD指针并重置暂存区

Git reset --hard xxx 本地库移动HEAD指针，充值暂存区，重置工作区

 Git diff用于比较文件差异，具体百度

 Git branch分支操作

 Git branch -v	查看分支

 Git branch hot_fix	创建hot_fix分支

 Git checkout hot_fix		切换到hot_fix分支

 Git merge hot_fix	将hot_fix分支中的修改同步到本分支中（现在已经切换到master）

git branch -d [name] (删除一个已经合并了的分支，如果强制删除一个分支，则用-D)

 

###  远程库基本操作

Git remote add mygithub http://xxxxxx	将远程库链接设置为mygithub，方便调用

Git remote -v	显示已经设置好的远程库链接，也可在config中查看，跟name一起

Git remote remove mygithub	删除设置好的mygithub

Git push mygithub master 将本地库的master分支推送到mygithub对应的远程库

- git push origin test:master	//提交本地分支test到远程master分支（origin为远程库地址）

- git push origin test:test		//提交本地分支test到远程test，如果没有则创建远程test

- git push origin :test		//：左边本地分支为空，表示删除远程test分支，但本地还保存

Git clone http://xxxx	将远程库克隆到本地目录，默认克隆master分支到本地

git clone -b <指定分支名> <远程仓库地址>：克隆远程指定分支，例如 git clone -b dev 仓库地址

Git fetch mygithub master	将mygithub远程库的master分支抓取到本地但不同步

Git checkout mygithub/master 切换到抓取到的mygithub，master分支

Git checkout master 切换到本地库master分支

以上两步用于对比文件信息，考虑要不要合并

Git merge mygithub/master 将抓取到的mygithub/master合并到本地库master库

git pull mygithub master 此命令相当于前面的先fetch再merge，一步达成同步

## windows下设置免输入用户名密码
在.gitconfig中输入如下代码
```shell
[credential]
        helper = store --file ~/.git-credentials
```
其中~/.git-credentials跟.gitconfig保存在同一目录，用于保存用户名密码，输入一次后以后即可自动输入
## git stash使用

（1）**git stash** save "save message" : 执行存储时，添加备注，方便查找，只有git stash 也要可以的，但查找时不方便识别。

（2）**git stash list** ：查看stash了哪些存储

（3）**git stash show** ：显示做了哪些改动，默认show第一个存储,如果要显示其他存贮，后面加stash@{$num}，比如第二个 git stash show stash@{1}

（4）**git stash show -p** : 显示第一个存储的改动，如果想显示其他存存储，命令：git stash show stash@{$num} -p ，比如第二个：git stash show stash@{1} -p

（5）**git stash apply** :应用某个存储,但不会把存储从存储列表中删除，默认使用第一个存储,即stash@{0}，如果要使用其他个，git stash apply stash@{$num} ， 比如第二个：git stash apply stash@{1} 

（6）**git stash pop** ：命令恢复之前缓存的工作目录，将缓存堆栈中的对应stash删除，并将对应修改应用到当前的工作目录下,默认为第一个stash,即stash@{0}，如果要应用并删除其他stash，命令：git stash pop stash@{$num} ，比如应用并删除第二个：git stash pop stash@{1}

（7）**git stash drop** stash@{$num} ：丢弃stash@{$num}存储，从列表中删除这个存储

（8）**git stash clear** ：删除所有缓存的stash

## git 撤销对工作区的修改

对工作区中文件的修改分为三种情况：

（1）还没有git add

（2）已经git add

（3）已经git add，并再次进行修改

对于第一种情况，直接使用git checkout -- 文件，即可撤销修改，撤销修改就回到和版本库一模一样的样子。

第二种情况，先使用git reset HEAD -- 文件，然后在使用git checkout -- 文件进行修改撤销。

第三种情况 先使用git checkout -- 文件，文件就会变成添加到暂存区后的状态，也就转换成了“第二种情况”，然后，在使用情况（2）中的处理方法，即可将文件恢复到与版本库一致的状态。

**总之，记住一点：“git checkout -- 文件”命令，撤销的是工作中文件的修改，而“git reset HEAD -- 文件”命令，撤销的是暂存区中文件的修改。**

## git clone

### git clone <远程仓库地址>：

默认克隆远程仓库master地址代码

### git clone -b <指定分支名> <远程仓库地址>

克隆远程指定分支，例如 git clone -b dev 仓库地址

## git push

git push origin test:master	//提交本地分支test到远程master分支（origin为远程库地址）

git push origin test:test		//提交本地分支test到远程test，如果没有则创建远程test

git push origin :test				//：左边本地分支为空，表示删除远程test分支，但本地还保存

## git pull

git pull <远程主机名> <远程分支名>:<本地分支名>

例：git pull origin next:master	//将远程库origin的next分支与本地的master分支合并

git pull origin next	//在本地next分支下执行本语句会默认拉取远程next分支到本地next分支

### git提交冲突后解决

git push origin xxxbranch遇到问题，推荐git pull下来

git pull origin xxxbranch 打开进行更改冲突的地方

git add .	

git commit -m "合并更新"

git push origin xxxbranch	OK!

### git 在所有分支中查询最近提交的关键字，找到对应的分支

已知版本关键字 ：BOCON_V50_190520_QH不知在哪个分支何时提交

git rev-list --all | xargs git grep "BOCON_V50_190520_QH" 找到def1d7761cee4bdcf8e3c668899b20002bd0a014	这次提交

使用git branch -r --contains def1d7761cee4bdcf8e3c668899b20002bd0a014 找到提交对应的远程分支



