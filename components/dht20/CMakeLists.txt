set(srcs "dht20.c")
set(dirs ".")

 if(CONFIG_TEST_DOUBLE)
     list(APPEND srcs "./mocks/dht20_mock.c")
     list(APPEND dirs "./mocks")
 endif()

idf_component_register(SRCS "${srcs}"
                     INCLUDE_DIRS "${dirs}"
                     )

#includeしているのはmath.hでも、明示的にtest_math.hをリンクして、同名の関数を定義しておけばオーバーライドできる
#通常のbuildはesp-idfの構成を使っている。
#platformioのtest機能は、unityを使っているがテストアプリのbuildはplatformio側で構成している。
    #esp-idfの構成（componentsにtestを含める）が使えない。と思う。
#Kconfigで設定した定数でビルドを変更する場合は、定数にCONFIG_をつけて参照すること