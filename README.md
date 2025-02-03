<h1 align="center">Search Engine</h1>
<h2>Description</h2>
The search engine implements the search for words in the specified text documents.
<h2>Demo</h2>
The search engine accepts 2 json files as input. The first file (the project cannot be started without it) it's called config.json. The second file requests.json contains a list of queries, which consists of a set of strings. At the output, the search engine generates the file answers.json containing the responses to each of the requests.
<dev>
<br>
<br>
For example.
<br>
<br>
Input data:
<br>
<br>
config.json
<pre>
{
  "config": {
      "name": "SearchEngine",
      "version": "1.0",
      "max_responses": 5
  },
  "files": [
      "C:\\file001.txt",
      "C:\\file002.txt",
      "C:\\file003.txt",
      "C:\\file004.txt"
   ]
}
</pre>
<br>
requests.json
<pre>
{
  "requests": [
    "milk water", 
    "sugar"
  ]
}
</pre>
</dev>
<br>
Output data:
<br>
<br>
The file has been generated answers.json with responses to requests.
<pre>
{
  "request001": {
    "relevance": {
      "docid_0": 0.7,
      "docid_1": 0.3,
      "docid_2": 1
    },
    "result": true
  },
  "request002": {
    "result": false
  }
}
</pre>
<br>
This means that the words from the first query were found in documents with identifiers docid_0, docid_1, docid_2. For the second query, no words were found in the documents, so the field "result" has the meaning of "false".
<h2>The technologies in the project</h2>
The project is written in C++14. The CMake project build system was used. The following third-party libraries are used: the library of the author nlohmann for working with json and the library from Google - googletests.
<h2>Technical description of the project</h2>
