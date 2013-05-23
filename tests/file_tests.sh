echo ">> Test date"
date +"%c"
echo ">> Testing version"
../lorem -v

# NEW FILE TESTS
echo ">> NEW FILE TESTS"
# test that default = 1 paragraph lorem
../lorem -o results/test1.txt
echo ">> Default = 1 paragraph created in test1.txt"
echo ">> This should result in 1"
rx subcount -i results/test1.txt Lorem
# 1 paragraph lorem
../lorem -n 1 -o results/test2.txt
echo ">> 1 paragraph created in test2.txt"
echo ">> This should result in 1"
rx subcount -i results/test2.txt Lorem
# 5 paragraphs lorem
../lorem -n 5 -o results/test3.txt
echo ">> 5 paragraphs created in test3.txt"
echo ">> This should result in 5"
rx subcount -i results/test3.txt Lorem
# 1000 paragraphs lorem
../lorem -n 1000 -o results/test4.txt
echo ">> 1000 paragraphs created in test4.txt"
echo ">> This should result in 1000"
rx subcount -i results/test4.txt Lorem

# 1 paragraph user supplied text with default n = 1
../lorem -t text_files/replace.txt -o results/test5.txt
echo ">> 1 paragraph of user text created in test5.txt"
echo ">> This should result in 1"
rx subcount -i results/test5.txt "Normally,"
# 1 paragraph user supplied text with -n specified write
../lorem -n 1 -t text_files/replace.txt -o results/test6.txt
echo ">> 1 paragraph of user text created in test6.txt"
echo ">> This should result in 1"
rx subcount -i results/test6.txt "Normally,"
# 5 paragraphs of user supplied text
../lorem -n 5 -t text_files/replace.txt -o results/test7.txt
echo ">> 5 paragraphs of user text created in test7.txt"
echo ">> This should result in 5"
rx subcount -i results/test7.txt "Normally,"
# 1000 paragraphs of user supplied text
../lorem -n 1000 -t text_files/replace.txt -o results/test8.txt
echo ">> 1000 paragraphs of user text created in test8.txt"
echo ">> This should result in 1000"
rx subcount -i results/test8.txt "Normally,"


echo ">> NEW FILE TESTS COMPLETE"
echo " "

#APPEND & TAG TESTS
echo ">> FILE APPEND & TAG TESTS"

../lorem -a -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test1.txt
echo ">> appended 1 paragraph with tags and user entered text to test1.txt using default n = 1"
echo ">> This should result in 1"
rx subcount -i results/test1.txt "Normally,"

../lorem -a -n 1 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test1.txt
echo ">> appended 1 paragraph with tags and user entered text to test1.txt using explicit n = 1"
echo ">> This should result in 2"
rx subcount -i results/test1.txt "Normally,"

../lorem -a -n 5 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test2.txt
echo ">> appended 5 paragraphs with tags and user entered text to test2.txt"
echo ">> This should result in 5"
rx subcount -i results/test2.txt "Normally,"

../lorem -a -n 1000 -b "<p class='samuel'>" -e "</p>" -t text_files/replace.txt -o results/test3.txt
echo ">> appended 1000 paragraphs with tags and user entered text to test3.txt"
echo ">> This should result in 1000"
rx subcount -i results/test3.txt "Normally,"

echo ">> TESTS COMPLETE"
echo " "

# SETUP FILE REPLACEMENT TESTS
#html with <lorem> in middle, test for pre and post strings with appropriate insertion
cp text_files/eg1.txt results/r1.txt
cp text_files/eg1.txt results/r2.txt 
cp text_files/eg1.txt results/r3.txt
cp text_files/eg1.txt results/r4.txt
cp text_files/eg1.txt results/r5.txt
cp text_files/eg1.txt results/r6.txt
cp text_files/eg1.txt results/r7.txt
cp text_files/eg1.txt results/r8.txt
cp text_files/eg1.txt results/r9.txt
cp text_files/eg1.txt results/r10.txt

# PERFORM FILE REPLACEMENT TESTS
echo ">> FILE REPLACEMENT TESTS"

## TEST INSERTION IN MIDDLE OF DOCUMENT
#default n = 1 paragraph of lorem replacement text
../lorem -r -i results/r1.txt
echo ">> default n=1 paragraph lorem insert in r1.txt"
#explicit n = 1 paragraph of lorem replacement text
../lorem -r -n 1 -i results/r2.txt
echo ">> explicit n=1 paragraph lorem insert in r2.txt"
#n = 5 paragraph of lorem insert
../lorem -r -n 5 -i results/r3.txt
echo ">> n=5 paragraph lorem insert in r3.txt"
#n = 1000 paragraph of lorem insert
../lorem -r -n 1000 -i results/r4.txt
#default n = 1 user submitted text replacement
echo ">> default n = 1 of user submitted text replacement in results/r5.txt"
../lorem -r -t text_files/replace.txt -i results/r5.txt
#explicit n = 1 user submitted text replacement
echo ">> explicit n = 1 of user submitted text replacement in results/r6.txt"
../lorem -r -n 1 -t text_files/replace.txt -i results/r6.txt
#n = 5 paragraphs of user submitted text replacement
echo ">> n=5 paragraphs of user submitted text replacement in results/r7.txt"
../lorem -r -n 5 -t text_files/replace.txt -i results/r7.txt
#n = 1000 paragraphs of user submitted text replacement
echo ">> n = 1000 paragraphs of user submitted text replacement in results/r8.txt"
../lorem -r -n 1000 -t text_files/replace.txt -i results/r8.txt
# n = 5 with tags around lorem text
echo ">> n = 5 paragraphs of lorem text with p tags around the paragraphs in results/r9.txt"
../lorem -r -n 5 -b "<p>" -e "</p>" -i results/r9.txt
# n = 5 with tags around user submitted text
echo ">> n = 5 paragraphs of user submitted text with p tags around the paragraphs in results/r10.txt"
../lorem -r -t text_files/replace.txt -n 5 -b "<p>" -e "</p>" -i results/r10.txt

echo ">> TESTS COMPLETE"
echo " "








