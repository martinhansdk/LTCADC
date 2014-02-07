g++ -o ltcadc_test -I .. -I $HOME/extcode/googletest-read-only/include/ ltcadc_test.cpp ../ltc_utility.cpp   -L $HOME/extcode/googletest-read-only/build -lgtest -lgtest_main -lpthread
./ltcadc_test
