# Setup Guide For osp-robot

# ネイティブ環境
- OS: Ubuntu 22.04
- ROS: ROS 2 Humble Hawksbill

# 1. Ubuntu22.04の環境を用意する

## 1.1 Ubuntu22.04のイメージを用意する
Ubuntu公式からUbuntu22.04 Desktop imageをダウンロードする<br>

[Ubuntu 22.04.4 LTS (Jammy Jellyfish)](https://releases.ubuntu.com/jammy/)

## 1.2 balenaEtcherを使ってUSBにイメージをインストールする

[balenaEtcher](https://etcher.balena.io/)

## 1.3 インストールUSBを元にしてロボット用のコンピュータにUbuntuをインストールする
[Ubuntu Desktop 22.04 LTS のインストール方法](https://kb.seeck.jp/archives/19354)

# 2. SSH経由で手元のパソコンから作業できるように設定する
```bash
sudo apt update
sudo apt upgrade
sudo apt install openssh-server
```
vscode上でssh接続するためには手元のUbuntuの環境に以下のような設定を行う。
```
sudo nano ~/.ssh/config
```
下記の内容を追加する

```bash
Host osp-nuc.local
  HostName osp-nuc.local
  User osp-nuc
  ForwardX11 yes
```
その後下記のサイトの<b>5. VS Code で SSH 接続する</b>からの手順でosp-nucを選択するとsshでロボット側のnucにアクセスすることができる。
[Visual Studio Code で Remote SSH する。](https://qiita.com/nlog2n2/items/1d1358f6913249f3e186)

またssh接続時にパスワードを省略したい場合したい場合は以下を実行する。
```bash
cat ~/.ssh/id_rsa.pub | ssh osp-nuc@osp-nuc.local "mkdir -p ~/.ssh; cat >> ~/.ssh/authorized_keys"
```

# 3. ROS2インストール
## 3.0 必要なaptパッケージ
```bash
sudo apt install git
```
## 3.1 aptリポジトリの追加

```bash
sudo apt update && sudo apt install curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```

## 3.2 リポジトリをsource listに追加

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

## 3.3 インストール

```bash
sudo apt update
sudo apt install ros-humble-desktop
```

##### 参考サイト
[ubuntu22.04にROS2 Humbleをインストールする](https://qiita.com/porizou1/items/5dd915402e2990e4d95f)

# 番外編1 GitHubにsshkeyを登録する
## 番外編1.1 sshディレクトリに移動する

```bash
cd ~/.ssh
```

## 番外編1.2 ssh key発行する

```bash
ssh-keygen -t rsa
```

色々表示出てくるけど、エンター押して飛ばしてください。

## 番外編1.3 ssh keyをコピーする

```bash
cat ~/.ssh/id_rsa.pub
```

catで表示してその後ssh-rsaから始まるkeyをコピーする（ctrl+shift+c）。catした時に表示される例は以下の通りです。

```bash
osp-nuc@osp-nuc:~$ sudo cat ~/.ssh/id_rsa.pub
ssh-rsa xxxxxxxxxxxxxxxxxxxxxx= osp-nuc@osp-nuc
```

## 番外編1.4 コピーしたkeyをGitHubに登録する
titleはosp-nuc@osp-nucのようなユーザー名@コンピューター名になるようにする。
Keyのところにssh-rsaから始まる内容を貼り付ける。

この一連の作業でGitHubと端末に紐付ける事ができる。
