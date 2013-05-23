echo ">> Test date:"
date +"%c"
echo ">> Testing version:"
../lorem -v

# STANDARD OUT TESTING with lorem text
echo ">> STANDARD OUT TESTS (LOREM TEXT)"
echo ">> This test should = 1"
../lorem -s | wc -l
echo ">> This test should = 1"
../lorem -s -n 1 | wc -l
echo ">> This test should = 5"
../lorem -s -n 5 | wc -l
echo ">> This test should = 1000"
../lorem -s -n 1000 | wc -l

echo ">> TEST BEGIN AND END TAGS WITH STD OUT"
echo ">> This test should show quotes around a single lorem paragraph"
../lorem -s -b '"' -e '"'
echo " "
echo ">> And so should this one"
../lorem -s -b '"'
echo " "
echo ">> And so should this one"
../lorem -s -e '"'
echo " "
echo ">> This should wrap p tags around five lorem paragraphs"
../lorem -s -b "<p>" -e "</p>" -n 5
echo " "
echo ">> This should include a class definition in the p tags around five lorem paragraphs"
../lorem -s -b "<p class='test'>" -e "</p>" -n 5
echo " "
echo ">> TESTS COMPLETE"
echo " "

# STANDARD OUT TESTING with user supplied text in replace.txt file
echo ">> STANDARD OUT TESTS (USER TEXT)"
echo ">> This test should count 344 characters"
../lorem -s -n 1 -t text_files/replace.txt | wc -c
echo ">> This test should count 1,720 characters"
../lorem -s -n 5 -t text_files/replace.txt | wc -c
echo ">> This test should count 344,000 characters"
../lorem -s -n 1000 -t text_files/replace.txt | wc -c
echo ">> This should print a paragraph of user text surrounded by quotes"
../lorem -s -n 1 -t text_files/replace.txt -b '"' -e '"'
echo " "
echo ">> And so should this"
../lorem -s -t text_files/replace.txt -b '"'
echo " "
echo ">> And so should this"
../lorem -s -t text_files/replace.txt -e '"'
echo " "
echo ">> TESTS COMPLETE"
echo " "







