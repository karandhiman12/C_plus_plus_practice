#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// Function to parse attributes from a string like 'attr1 = "value1" attr2 = "value2"'
map<string, string> parseAttributes(string attrStr) {
    map<string, string> attributes;
    
    // Remove extra spaces and clean up the string
    stringstream ss(attrStr);
    string token;
    vector<string> tokens;
    
    // Split by spaces but be careful with quoted values
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    // Process tokens to extract attribute-value pairs
    for (int i = 0; i < tokens.size(); ) {
        if (i + 2 < tokens.size() && tokens[i + 1] == "=") {
            string attrName = tokens[i];
            string value = tokens[i + 2];
            
            // Remove quotes from value
            if (value.length() >= 2 && value[0] == '"' && value[value.length()-1] == '"') {
                value = value.substr(1, value.length() - 2);
            }
            
            attributes[attrName] = value;
            i += 3;
        } else {
            i++;
        }
    }
    
    return attributes;
}

int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore(); // Ignore the newline after reading n and q
    
    // Stack to keep track of current tag path
    vector<string> tagStack;
    
    // Map to store attributes for each complete path
    // Key: "tag1.tag2.tag3", Value: map of attribute->value
    map<string, map<string, string>> pathAttributes;
    
    // Process HRML lines
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        // Check if it's a closing tag
        if (line.find("</") == 0) {
            // Closing tag - pop from stack
            if (!tagStack.empty()) {
                tagStack.pop_back();
            }
        } else {
            // Opening tag
            // Extract tag name and attributes
            int start = line.find('<') + 1;
            int end = line.find('>');
            string content = line.substr(start, end - start);
            
            // Find first space to separate tag name from attributes
            int spacePos = content.find(' ');
            string tagName;
            string attrStr = "";
            
            if (spacePos != string::npos) {
                tagName = content.substr(0, spacePos);
                attrStr = content.substr(spacePos + 1);
            } else {
                tagName = content;
            }
            
            // Add current tag to stack
            tagStack.push_back(tagName);
            
            // Build current path
            string currentPath = "";
            for (int j = 0; j < tagStack.size(); j++) {
                if (j > 0) currentPath += ".";
                currentPath += tagStack[j];
            }
            
            // Parse and store attributes if they exist
            if (!attrStr.empty()) {
                map<string, string> attrs = parseAttributes(attrStr);
                pathAttributes[currentPath] = attrs;
            }
        }
    }
    
    // Process queries
    for (int i = 0; i < q; i++) {
        string query;
        getline(cin, query);
        
        // Find the '~' separator
        int tildePos = query.find('~');
        if (tildePos != string::npos) {
            string path = query.substr(0, tildePos);
            string attrName = query.substr(tildePos + 1);
            
            // Check if path exists and has the requested attribute
            if (pathAttributes.find(path) != pathAttributes.end() && 
                pathAttributes[path].find(attrName) != pathAttributes[path].end()) {
                cout << pathAttributes[path][attrName] << endl;
            } else {
                cout << "Not Found!" << endl;
            }
        } else {
            cout << "Not Found!" << endl;
        }
    }
    
    return 0;
}

/*
Sample Input:
4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value

Expected Output:
Name1
Not Found!
HelloWorld

How it works:
1. Read each HRML line
2. If it's a closing tag (</tagname>), pop from the tag stack
3. If it's an opening tag:
   - Extract tag name and attributes
   - Push tag name to stack
   - Build current path by joining stack with dots
   - Parse and store attributes for this path
4. For each query:
   - Split by '~' to get path and attribute name
   - Look up the path in our pathAttributes map
   - Return the attribute value or "Not Found!"

Example trace for sample:
- <tag1 value = "HelloWorld"> -> path="tag1", attrs={"value":"HelloWorld"}
- <tag2 name = "Name1"> -> path="tag1.tag2", attrs={"name":"Name1"}
- </tag2> -> pop tag2
- </tag1> -> pop tag1

Query trace:
- tag1.tag2~name -> pathAttributes["tag1.tag2"]["name"] = "Name1"
- tag1~name -> pathAttributes["tag1"]["name"] doesn't exist -> "Not Found!"
- tag1~value -> pathAttributes["tag1"]["value"] = "HelloWorld"
*/