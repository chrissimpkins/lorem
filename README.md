lorem
=====

A dummy text generator and text replacement application that creates new text files, inserts or appends text in existing files, or prints it to the standard out stream (so that you can pipe it to whatever you'd like).

### NEW
Use your own dummy text (or any replacement text) by including the insertion text file path after the -t option.  <a href="#owntext">More information below</a>.

<a href="http://j.mp/LOREM">http://j.mp/LOREM</a>

## Installation
Open your terminal in the main source directory and then:
<pre>./configure</pre>
<pre>make</pre>
<pre>sudo make install</pre>
## Use Examples

### Create a New File with Dummy Text
<p>Say you want to create a new file named 'eg.txt' with 5 paragraphs of dummy text. Use the following command:</p>
<pre>lorem -n 5 -o eg.txt</pre>

### Append Dummy Text to an Existing Text File
<p>You have a file named 'eg.txt' and you would like to append 10 paragraphs of dummy text to it. Use the following command:</p>
<pre>lorem -a -n 10 -o eg.txt</pre>

### Insert Dummy Text into a Specific Location in an Existing Text File
<p>Say you have the following html file named 'eg.html':</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang="en"&gt;
&lt;head&gt;
&lt;meta charset="utf-8" /&gt;
&lt;title&gt;Lorem example&lt;/title&gt;
&lt;link rel="stylesheet" href="css/main.css" type="text/css" /&gt;
&lt;/head&gt;
&lt;body id="index" class="home"&gt;
&lt;p class="main_paragraph"&gt;
  
&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>
<p>Add the delimiter <code>&lt;lorem&gt;</code> to the file like this (it's between the p tags):</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang="en"&gt;
&lt;head&gt;
&lt;meta charset="utf-8" /&gt;
&lt;title&gt;Lorem example&lt;/title&gt;
&lt;link rel="stylesheet" href="css/main.css" type="text/css" /&gt;
&lt;/head&gt;
&lt;body id="index" class="home"&gt;
&lt;p class="main_paragraph"&gt;
&lt;lorem&gt;
&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>
<p>Then run the following to insert a paragraph of lorem text at the site of the <lorem> delimiter:</p>
<pre>lorem -r -i eg.html</pre>
<p>And here is what you get:</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang="en"&gt;
&lt;head&gt;
&lt;meta charset="utf-8" /&gt;
&lt;title&gt;Lorem example&lt;/title&gt;
&lt;link rel="stylesheet" href="css/main.css" type="text/css" /&gt;
&lt;/head&gt;
&lt;body id="index" class="home"&gt;
&lt;p class="main_paragraph"&gt;
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>
<p>Rinse and repeat as desired.  Use the -n option to insert more than one paragraph.</p>

### Insert Tags Before and After Each Paragraph
<p>If you want to wrap each paragraph with it's own set of tags, you can enter them with the -b and -e options (for begin and end). Make sure that you use quotes around special characters on the command line. This includes the &lt; and &gt; symbols.</p>

<p>Here is an example of how you would make five paragraphs of dummy text wrapped with a p tag that has a class.</p>

<p>The file before the insert with the <code>&lt;lorem&gt;</code> delimiter included between the body tags:</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang="en"&gt;
&lt;head&gt;
&lt;meta charset="utf-8" /&gt;
&lt;title&gt;Lorem example&lt;/title&gt;
&lt;link rel="stylesheet" href="css/main.css" type="text/css" /&gt;
&lt;/head&gt;
&lt;body id="index" class="home"&gt;
&lt;lorem&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>

<p>Enter the following command:</p>
<pre>lorem -r -n 5 -b &quot;&lt;p class='coolclass'&gt;&quot; -e &quot;&lt;/p&gt;&quot;</pre>
<p>And here is what you get:</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang="en"&gt;
&lt;head&gt;
&lt;meta charset="utf-8" /&gt;
&lt;title&gt;Lorem example&lt;/title&gt;
&lt;link rel="stylesheet" href="css/main.css" type="text/css" /&gt;
&lt;/head&gt;
&lt;body id="index" class="home"&gt;
&lt;p class='coolclass'&gt;Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.&lt;/p&gt;
&lt;p class='coolclass'&gt;Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.&lt;/p&gt;
&lt;p class='coolclass'&gt;Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.&lt;/p&gt;
&lt;p class='coolclass'&gt;Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.&lt;/p&gt;
&lt;p class='coolclass'&gt;Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.&lt;/p&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>

Ta da!

<h3 id="owntext">Bring Your Own Dummy Text</h3>
<p>If you want to use your own dummy text in replacements, include the file path to the dummy text file following the -t option.</p>
<p>Here is an example of how to include 10 blocks of your own text that is included in a file on the path path/to/replacement.txt and is inserted in the location of the <code>&lt;lorem&gt;</code> delimiter of a file on the path path/to/insertfile.txt</p>

<pre>lorem -r -n 10 -i path/to/insertfile.txt -t path/to/replacement.txt</pre>

<p>Voila!</p>

### Pipe Dummy Text to Another Application
<p>lorem will write up to one million paragraphs of dummy text to the standard out stream.  Pipe it to whatever you like.</p>
<pre>lorem -s -n 1000000 | wc -c</pre>

## Help
Enter the following for help:
<pre>lorem -h</pre>
All of the available options are detailed.


