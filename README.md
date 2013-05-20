lorem
=====

A lorem ipsum dummy text generator that creates new text files, inserts or appends dummy text in existing files, or prints it to standard out.

## Installation
Open your terminal in the main source directory and then:
<pre>./configure</pre>
<pre>make</pre>
<pre>sudo make install</pre>
## Use Examples
### Insert in an Existing Text File
<p>Say, you have the following html file named 'eg.html':</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang=&quot;en&quot;&gt;
&lt;head>
&lt;meta charset=&quot;utf-8&quot; /&gt;
&lt;title>Lorem example&lt;/title&gt;
 
&lt;link rel=&quot;stylesheet&quot; href=&quot;css/main.css&quot; type=&quot;text/css&quot; /&gt;
 
&lt;!--[if IE]&gt;
	&lt;script src=&quot;http://html5shiv.googlecode.com/svn/trunk/html5.js&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lte IE 7]&gt;
	&lt;script src=&quot;js/IE8.js&quot; type=&quot;text/javascript&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lt IE 7]&gt;
 
	&lt;link rel=&quot;stylesheet&quot; type=&quot;text/css&quot; media=&quot;all&quot; href=&quot;css/ie6.css&quot;/&gt;&lt;![endif]--&gt;
&lt;/head&gt;
 
&lt;body id=&quot;index&quot; class=&quot;home&quot;&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>
<p>Add the delimiter `<lorem>` to the file like this:</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang=&quot;en&quot;&gt;
&lt;head>
&lt;meta charset=&quot;utf-8&quot; /&gt;
&lt;title>Lorem example&lt;/title&gt;
 
&lt;link rel=&quot;stylesheet&quot; href=&quot;css/main.css&quot; type=&quot;text/css&quot; /&gt;
 
&lt;!--[if IE]&gt;
	&lt;script src=&quot;http://html5shiv.googlecode.com/svn/trunk/html5.js&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lte IE 7]&gt;
	&lt;script src=&quot;js/IE8.js&quot; type=&quot;text/javascript&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lt IE 7]&gt;
 
	&lt;link rel=&quot;stylesheet&quot; type=&quot;text/css&quot; media=&quot;all&quot; href=&quot;css/ie6.css&quot;/&gt;&lt;![endif]--&gt;
&lt;/head&gt;
 
&lt;body id=&quot;index&quot; class=&quot;home&quot;&gt;
&lt;lorem&gt;
&lt;/body&gt;
&lt;/html&gt;
</pre>
<p>Then run the following to insert 5 paragraphs of lorem text at the site of the <lorem> delimiter:</p>
<pre>lorem -r -n 5 -i eg.html</pre>
<p>And here is what you get:</p>
<pre>
&lt;!DOCTYPE html&gt;
&lt;html lang=&quot;en&quot;&gt;
&lt;head>
&lt;meta charset=&quot;utf-8&quot; /&gt;
&lt;title>Lorem example&lt;/title&gt;
 
&lt;link rel=&quot;stylesheet&quot; href=&quot;css/main.css&quot; type=&quot;text/css&quot; /&gt;
 
&lt;!--[if IE]&gt;
	&lt;script src=&quot;http://html5shiv.googlecode.com/svn/trunk/html5.js&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lte IE 7]&gt;
	&lt;script src=&quot;js/IE8.js&quot; type=&quot;text/javascript&quot;&gt;&lt;/script&gt;&lt;![endif]--&gt;
&lt;!--[if lt IE 7]&gt;
 
	&lt;link rel=&quot;stylesheet&quot; type=&quot;text/css&quot; media=&quot;all&quot; href=&quot;css/ie6.css&quot;/&gt;&lt;![endif]--&gt;
&lt;/head&gt;
 
&lt;body id=&quot;index&quot; class=&quot;home&quot;&gt;
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
&lt;/body&gt;
&lt;/html&gt;
</pre>
