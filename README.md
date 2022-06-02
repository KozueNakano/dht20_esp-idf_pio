How to Unit testing PlatformIO based esp-idf project
=====================================
## tips
- platformioで構築したesp-idf環境は、buildは基本的にesp-idfの仕組みが使われている。  
    componentsのCMakeの書き方は、esp-idfのrefが参考になる。
- unit testをplatformioのメニューから行うと、Unityのappの構築が、Platformio側で行われてるっぽくて、  
    esp-idfのComponentsのUnityのテストプロジェクトと同じ構成だと構築されない。
    - esp-idfでは、componentsにテストも含めるような構成を推奨しているけど、  
        platromioのメニューのテストでは、mainディレクトリのtestディレクトリにテストをまとめて配置したtestを構築する。
- 以上から、テストダブルはcomponentsに配置して、テストappだけtestディレクトリに配置すると、platformioのUIを使ってテストダブルを使ったUnitテストが実行できる。
- テストダブルと本番モジュールの切り替えは、
    - 置き換えたい関数と同名の関数を含んだ、テストダブルの.c .h を作る。
    - CMakeでそれらをbuildに追加するとオーバーライドできる。
    - CMakeでリンクするかどうか選択するには、Kconfigのmenuで選択できるようにするのが使いやすいと思う。
        - Kconfigで定義された定数をCMakeで参照するには、CONFIG_を定数名につける。

        　　
## Hou to Run tests
- vscodeのpioのエクステンションのメニューから、esp32dev-Advance-testで、テストアプリがbuildされて、ターゲットでrunする。


How to build PlatformIO based project
=====================================

1. [Install PlatformIO Core](https://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-espressif32/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```shell
# Change directory to example
$ cd platform-espressif32/examples/espidf-blink

# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Build specific environment
$ pio run -e esp32dev

# Upload firmware for the specific environment
$ pio run -e esp32dev --target upload

# Clean build files
$ pio run --target clean
```