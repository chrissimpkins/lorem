# NEW FILE TESTS
echo "FILE TESTS"
# test that default = 1 paragraph lorem
../lorem -o results/test_default.txt
echo "Default = 1 paragraph created in test_default.txt"
# 1 paragraph
../lorem -n 1 -o results/test1.txt
echo "1 paragraph created in test1.txt"

# 5 paragraphs
../lorem -n 5 -o results/test2.txt
echo "5 paragraphs created in test2.txt"
# 1000 paragraphs
../lorem -n 1000 -o results/test3.txt
echo "1000 paragraphs created in test3.txt"

echo "TESTS COMPLETE"
echo " "

#APPEND & TAG TESTS
echo "APPEND TESTS"
../lorem -a -n 1 -b "<p class='samuel'>" -e "</p>" -t replace.txt -o results/test1.txt
echo "appended 1 paragraph with tags and user entered text to test1.txt"
../lorem -a -n 5 -b "<p class='samuel'>" -e "</p>" -t replace.txt -o results/test2.txt
echo "appended 5 paragraphs with tags and user entered text to test2.txt"
../lorem -a -n 1000 -b "<p class='samuel'>" -e "</p>" -t replace.txt -o results/test3.txt
echo "appended 1000 paragraphs with tags and user entered tet to test3.txt"
echo "TESTS COMPLETE"
echo " "

# 
../lorem -n 1 -t replace.txt -o results/test4.txt
echo "1 paragraph of user text created in test4.txt"
../lorem -n 5 -t replace.txt -o results/test5.txt
echo "5 paragraphs of user text created in test5.txt"
../lorem -n 1000 -t replace.txt -o results/test6.txt
echo "1000 paragraphs of user text created in test6.txt"