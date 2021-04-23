find $1 -regextype posix-extended -regex ".*\.[hc]pp" | xargs clang-format -i
