# GisL 中的设计模式

软件开发中设计模式很重要。

## 命令模式

命令模式在 GUI 程序中极为常见，能做到命令的撤销与重做。

```shell
tree src/gui/command

src/gui/command
├── command.cpp
├── command.h
├── commandhistory.cpp
├── commandhistory.h
├── openrastercommand.cpp
├── openrastercommand.h
├── opensldcommand.cpp
├── opensldcommand.h
├── openvectorcommand.cpp
└── openvectorcommand.h
```

其头文件设计如下：

```c++
class Command : public QObject {
  Q_OBJECT
public:
  enum class CommandErr {
    NoErr = 0,
    InputErr = 1,
    OutputErr = 2,
  };

  virtual void execute(QWidget* parent) = 0;
  virtual void reverse() = 0;

  virtual const std::string& output() = 0;

  virtual ~Command();

  [[nodiscard]] constexpr bool hasError() const noexcept;
  [[nodiscard]] std::string_view errorMessage() const;

protected:
  Command() = default;

  CommandErr _mErr = CommandErr::NoErr;
  std::string _errorMessage;
};
```
