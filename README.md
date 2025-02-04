<h1 align="center">Search Engine</h1>
<h2>Description</h2>
The search engine implements the search for words in the specified text documents.
The program reads the input data from 2 config files.json and requests.json (the program searches for files in the current directory). The input files must strictly conform to the format.
<dev>
<br>
<br>
The file config.json must contain 2 fields:
<p>
The "config" field contains an json-object with the fields "name", "version" and "max_responses". The "name" field indicates the name of the project, the "version" field indicates the project version, and the "max_responses" field indicates the number of responses to be given to each of the requests. That is, if, for example, 10 responses are found for one request, and the "max_responses" field contains the value 3, that's in the final answers file.There will be 3 json responses to this request. If the "max_responses" field is not specified, then by default the number of responses to each of the requests is 5.
</p>
<p>
The second field "files" is an array of strings that contain the absolute paths to the files in which the words are searched.
</p>
<p>
The files in which the search is performed must contain no more than 1000 words each, and each word must contain no more than 100 characters.
</p>
<br>
The file requests.json contains a single "requests" field, which is an array of strings. Each line is a set of words that the program will search for in the fields specified in config.json documents. Each line (query) can contain from 1 to 10 words. The "requests" array can contain no more than 1000 requests.
<br>
<br>
As a result of the program, the file answers.json is generated. The file contains the fields "request001", "request002"... . The number of fields is equal to the number of requests in the file requests.json. The request number in the "request..." field corresponds to the position number where the request was located in the "requests" field of the "requests.json" file. For example, the response to a request located at position 1 in the "requests" field will have the name of the "request001" field in the "answers.json"
If the response to the request was not found, then the value "false" is written in the "result" field of the "request..." field. Otherwise, "true" is written.
<br>
<br>
If an answer to the query has been found, a field with the value "docid_0" : 1.0 is formed. Here, the field name represents the number of the document in which the words from the query were found. This number corresponds to the document position number in the "fields" array in the "config.json" file. The value of the "docid_..." field is called the rank, and is calculated according to a certain formula. This field takes a value strictly greater than 0 and less than and equal to 1. It shows how much the file matches the search query.
<br>
If several documents were found for the query, then the "relevance" field is created in the "request..." field, which contains a list of fields "docid_0" : 0.5, "docid_1" : 0.3 ..., that is, as many fields as the words for the query and their corresponding rank were found in how many documents.
</dev>
<h2>Demo</h2>
The search engine accepts 2 json files as input. The first file (the project cannot be started without it) it's called config.json. The second file requests.json contains a list of queries, which consists of a set of strings. At the output, the search engine generates the file answers.json containing the responses to each of the requests.

<dev>
<br>
<br>
For example.
<br>
<br>
The directory with the program before its launch.
<img src=https://github.com/user-attachments/assets/b7d3a1f5-6efe-4009-9145-8a4ac7bac4c7>

Input data:

<br>
<img src="https://github.com/user-attachments/assets/e4dbe8cb-a57c-487c-ac5f-7778ade04fc5">

<pre>
{
  "config": {
      "name": "drifting searcher",
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
<img src="https://github.com/user-attachments/assets/308da529-d877-421c-ae5b-077a7dab3b18" alt="files">
The file "C:\\file001.txt" contains the string "milk milk milk milk water water water"
<br>
The file "C:\\file002.txt" contains the string "milk water water"
<br>
The file "C:\\file003.txt" contains the string "milk milk milk milk milk water water water water water"
<br>
The file "C:\\file004.txt" contains the string "americano cappuccino"
<br>
<br>
<img src="https://github.com/user-attachments/assets/4ac16431-f968-444c-bc5d-5c72611d73c2" alt="file requests.json">
<pre>
{
  "requests": [
    "milk water", 
    "sugar",
    "cappuccino"
  ]
}
</pre>
</dev>
<br>
To run the program, open the terminal and go to the folder where the program is located. Then enter the "Starting" command. the terminal will display the label that is specified in the "name" field in the file config.json. After that, a file with answers to the queries "answers.json". If the file was generated earlier, the contents will be overwritten.
<img src=https://github.com/user-attachments/assets/cf338cb8-a1a7-4a34-8f51-2f508c40214f>

<br>
<br>
The directory with the program after its launch.
<img src=https://github.com/user-attachments/assets/b85d53c2-9e6f-4acc-8691-924ba791bb28>


Output data:
<br>
<br>
The file has been generated answers.json with responses to requests.
<img src="https://github.com/user-attachments/assets/796d3d8a-4571-4a02-80eb-7012465a7d82" alt="file answers.json">
<pre>
{
    "request001": {
        "relevance": {
            "docid_0": 0.7,
            "docid_1": 0.3,
            "docid_2": 1.0
        },
        "result": true
    },
    "request002": {
        "result": false
    },
    "request003": {
        "docid_0": 1.0,
        "result": true
    }
}
</pre>
<br>
This means that the words from the first query were found in documents with identifiers 0, 1 and 2. The "relevance" field was created, in which the fields "docid_0", "docid_1", "docid_2" were placed. For the second query, no words were found in the documents, so the field "result" has the meaning of "false". For the third query, the word was found in only one document.
<h2>The technologies in the project</h2>
The project is written in C++14. The CMake project build system was used. The following third-party libraries are used: the library of the author nlohmann for working with json and the library from Google - googletests.
<h2>Architecture features</h2>
The program does not search for words directly in each file, but uses a data structure - an inverted index, in which for each word in the document collection, all documents in the collection in which it was found are listed in the corresponding list. This eliminates the need to open and read documents with each request, which increases productivity.
<h2>Technical description of the project</h2>
<h3>For developers</h3>
In order to build and run a project in the IDE, you need to copy this repository using standard git commands (git clone, etc.). Open the project in any IDE and configure the connection of the nlohmann json library in accordance with the instructions provided on <a href="https://github.com/nlohmann/json?ysclid=m6qb5f5krf698243886">the library page on github</a>.
Then, in the src directory with the file main.cpp create file config.json and requests.json in the format shown in the demo example 
and launch the project. 
as a result, the file answers.json will appear in the src directory, which contains responses to all requests from the file requests.json.
<h3>For users</h3>
To start the search engine, the first step is to add the paths to the libraries libwinpthread-1.dll , libstdc++-6.dll , libgcc_s_seh-1.dll in the system variable Path. Then, in the directory with the executable file Starting.exe create files config.json and requests.json in accordance with the format shown in the demo example. To run the program, open the terminal and go to the directory with the program and files config.json and requests.json. Enter the "Starting" command. As a result, a file will be generated in the same directory, which contains responses to all requests from the file requests.json.
