#include<iostream>
#include<vector>
#include<string>
#include<fstream>


using namespace std;


class DocumentElement{

    public: 
    virtual string render()=0;
};

class TextElement : public DocumentElement{
private : 
    string text;

    public:
    TextElement(string t){
        this->text=t;
    }
    
    string render(){
        return text;
    }

};

class ImageElement : public DocumentElement{
    private : 
        string imgPath;
    
        public:
        ImageElement(string t){
            this->imgPath=t;
        }
        
        string render(){
            return imgPath;
        }
    
    };

class newLineElement : public DocumentElement{
        
    public:
            
        string render(){
            return "\n";
        }
        
};

class Document{

    vector<DocumentElement*> documentElements;

public:
    void addElement(DocumentElement* ele){
        documentElements.push_back(ele);
    }

    string render(){
        string result="";

        for(auto ele:documentElements){
            result=result+ele->render();
        }
    return result;

    }
};

class Persistence{
public:
   virtual void save(string data)=0;

};

class FileStorage : public Persistence {
public:

void save(string s){
    ofstream outFile("document.txt");
    if(outFile){
        outFile << s;
        outFile.close();
        cout<<"Document saved to document.txt"<<endl;
    }
    else{
        cout<<"Error : Unable to open file for writing";
    }
}

};


class DBStorage : public Persistence {
    public:
    
    void save(string s){
        cout<<"saved to DB "<<endl;
    }
    
};


// class Document Editor
class DocumentEditor{

    Document* doc;
    Persistence* storage;
    string renderedDocument;

public:

    DocumentEditor(Document* d, Persistence* p){
        this->doc=d;
        this->storage=p;
    }
    void addText(string text){
        doc->addElement(new TextElement(text));
    }
    void addImg(string imgPath){
        doc->addElement(new ImageElement(imgPath));
    }
    void addNewLine(){
        doc->addElement(new newLineElement());
    }

    string renderDocument(){
         renderedDocument= doc->render();
         return renderedDocument;
    }

    void saveDocument(){
        storage->save(renderedDocument);
    }


};



