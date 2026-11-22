# cppsoeasy

基于 [Docsify](https://docsify.js.org/) 的 C++ 知识库，以 C++11 为主，兼顾部分 C++14 / C++17，整理面试知识点与刷题记录。

在线预览：<https://github.com/ShiverZm/cppsoeasy>

## 内容概览

| 目录 | 说明 |
|------|------|
| `docs/1-基础` | 语法、指针引用、面向对象等基础 |
| `docs/2-高级` | 容器、模板、智能指针、C++17 等 |
| `docs/3-网络` | HTTP 等网络相关 |
| `docs/4-多线程` | 线程与并发 |
| `docs/5-算法` | 刷题与算法笔记 |
| `docs/6-数据库` | 数据库相关 |
| `docs/7-数据结构` | 链表、栈队列、树等 |
| `docs/8-操作系统` | 操作系统 |
| `docs/9-计算机组成原理` | 组成原理 |
| `docs/10-编译原理` | 编译原理 |
| `docs/设计模式` | 创建型 / 结构型 / 行为型 |
| `docs/Qt` / `docs/Windows` / `docs/Linux` | 平台与框架 |
| `docs/面试题集` | 面试题整理 |

## 本地运行（Docsify）

本仓库入口在项目根目录的 `index.html`，文档正文在 `docs/`，侧边栏为根目录 `_sidebar.md`。

### 1. 环境要求

- [Node.js](https://nodejs.org/)（含 npm）

### 2. 安装 docsify-cli

```bash
npm i docsify-cli -g
```

或不全局安装，改用 `npx`：

```bash
npx docsify-cli serve .
```

### 3. 启动本地预览

在**项目根目录**执行：

```bash
docsify serve .
```

浏览器访问：<http://localhost:3000>

常用参数：

```bash
# 指定端口
docsify serve . --port 8080

# 启动后自动打开浏览器
docsify serve . --open
```

> 注意：请使用 `docsify serve .`（根目录），不要写成 `docsify serve docs`。  
> 本项目的 `index.html`、`_sidebar.md` 在根目录，文档在 `docs/`。

### 4. 其他简易方式

任意静态服务器均可预览，例如：

```bash
# Python 3
python -m http.server 3000

# VS Code / Cursor：用 Live Server 打开根目录 index.html
```

## 目录结构

```text
cppsoeasy/
├── index.html      # Docsify 入口与插件配置
├── _sidebar.md     # 左侧导航
├── .nojekyll       # 供 GitHub Pages 使用
├── docs/           # Markdown 文档
│   └── README.md   # 站点首页
├── images/         # 图片资源
└── README.md       # 本说明
```

## 编写文档

1. 在 `docs/` 对应分类下新增 `.md` 文件  
2. 重新生成侧边栏：

```bash
# Git Bash / macOS / Linux
bash generate_sidebar.sh

# Windows 也可指定 Git Bash 路径，例如：
# "D:\tool\Git\bin\bash.exe" generate_sidebar.sh
```

脚本会扫描 `docs/`，覆盖生成根目录 `_sidebar.md`（跳过空目录、根目录 `README.md` / `style.md`）。

3. 本地执行 `docsify serve .` 预览效果

## 部署到 GitHub Pages

1. 仓库 Settings → Pages  
2. Source 选择分支（如 `main`），目录选 `/`（根目录）  
3. 已包含 `.nojekyll`，下划线开头的 `_sidebar.md` 可被正确访问  

## 参考资料

- [Cpp Reference](https://zh.cppreference.com/w/cpp)
- [帅地玩编程 C++ 面试题](https://www.iamshuaidi.com/2529.html)
- [C语言中文网](http://c.biancheng.net/stl/stl_basic/)
- [程序厨的算法小屋](https://www.chengxuchu.com/#/)

欢迎纠错与补充。
