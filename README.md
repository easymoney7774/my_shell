# 🐚 MyShell - A Simple Unix-like Shell in C

> 一个使用 C 语言实现的简易类 Unix Shell，支持常见的命令执行、内建命令、重定向、管道、命令补全、历史记录与别名功能，适合作为操作系统课程设计项目。

---

## 🔧 功能特性 Features

- ✅ 外部命令执行（支持参数）
- ✅ 内建命令支持：
  - `cd`：切换工作目录
  - `exit`：退出 shell
  - `alias` / `unalias`：管理命令别名
  - `history` / `!n`：历史命令查看与执行
- ✅ I/O 重定向：
  - `>`：输出重定向
  - `>>`：输出追加
  - `<`：输入重定向
- ✅ 管道支持：`cmd1 | cmd2`
- ✅ 后台运行：命令后加 `&`
- ✅ 命令自动补全（依赖 readline）
- ✅ 历史记录管理
- ✅ 命令别名管理
- ✅ 模块化结构，易于维护和扩展

---

## 🧱 系统设计架构

```text
main.c
 ├── parser.c       // 命令参数解析
 ├── builtin.c      // 内建命令处理
 ├── alias.c        // alias / unalias 管理
 ├── history.c      // 历史命令记录与回调
 ├── executor.c     // 命令执行（支持重定向、管道）
 ├── utils.c        // 辅助打印、提示符等
 └── include/       // 所有头文件定义
```

---

## 📦 文件结构

```text
my_shell/
├── src/             # 所有源代码文件
├── include/         # 所有头文件（.h）
├── obj/             # 编译生成的 .o 文件
├── my_shell         # 编译生成的可执行文件
├── Makefile         # 一键编译脚本
└── README.md        # 项目说明文档
```

---

## 💻 编译与运行

### ✅ 安装依赖（仅需一次）

```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

### ✅ 编译

```bash
make
```

### ✅ 运行 Shell

```bash
./my_shell
```

---

## 🚀 示例命令演示

```bash
cd ..
pwd
alias ll='ls -l'
ll
unalias ll
history
!2

echo hello > file.txt
cat < file.txt | wc -l

sleep 3 &
```

---

## 🌟 效果截图（建议添加）

你可以插入终端运行截图，显示功能效果，例如：

```
========== My Shell ==========
my_shell$ alias ll='ls -l'
my_shell$ ll
total 20
-rw-r--r-- 1 user user  1234 Jul 7  main.c
...
```

---

## 📌 已知限制 & 待开发功能

| 功能                    | 状态     | 说明                       |
|-------------------------|----------|----------------------------|
| 多级管道支持 `cmd1 | cmd2 | cmd3` | ❌ 未实现 | 可扩展为递归解析 |
| 脚本文件支持 `.sh`      | ❌ 未实现 | 可支持读取执行脚本 |
| 别名/历史持久化         | ❌ 未实现 | 可写入文件保存 alias/history |
| 环境变量处理 `$HOME`    | ❌ 未实现 | 可配合 `getenv()` 实现 |

---

## 👨‍💻 作者信息

- 作者：[@easymoney7774](https://github.com/easymoney7774)
- 邮箱：1265309411@qq.com
- 项目地址：[GitHub 链接](https://github.com/easymoney7774/my_shell)

---

## 📄 License

本项目采用 [MIT License](https://opensource.org/licenses/MIT)，可自由修改与发布，欢迎 star 和 issue！
