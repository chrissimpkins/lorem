# NEW FILE TESTS
echo "NEW FILE TESTS"
# test that default = 1 paragraph lorem
../lorem -o results/test1.txt
echo "Default = 1 paragraph created in test1.txt"

# 1 paragraph lorem
../lorem -n 1 -o results/test2.txt
echo "1 paragraph created in test2.txt"

# 5 paragraphs lorem
../lorem -n 5 -o results/test3.txt
echo "5 paragraphs created in test3.txt"

# 1000 paragraphs lorem
../lorem -n 1000 -o results/test4.txt
echo "1000 paragraphs created in test4.txt"

# 1 paragraph user supplied text with default write
../lorem -t text_files/replace.txt -o results/test5.txt
echo "1 paragraph of user text created in test5.txt"
# 1 paragraph user supplied text with -n specified write
../lorem -n 1 -t text_files/replace.txt -o results/test6.txt
echo "1 paragraph of user text created in test6.txt"
# 5 paragraphs of user supplied text
../lorem -n 5 -t text_files/replace.txt -o results/test7.txt
echo "5 paragraphs of user text created in test7.txt"
# 1000 paragraphs of user supplied text
../lorem -n 1000 -t text_files/replace.txt -o results/test8.txt
echo "1000 paragraphs of user text created in test8.txt"


echo "NEW FILE TESTS COMPLETE"
echo " "

#APPEND & TAG TESTS
echo "APPEND TESTS"
../lorem -a -n 1 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test1.txt
echo "appended 1 paragraph with tags and user entered text to test1.txt"
../lorem -a -n 5 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test2.txt
echo "appended 5 paragraphs with tags and user entered text to test2.txt"
../lorem -a -n 1000 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test3.txt
echo "appended 1000 paragraphs with tags and user entered tet to test3.txt"
echo "TESTS COMPLETE"
echo " "

