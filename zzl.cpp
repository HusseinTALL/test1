#include <iostream>
#include<fstream>
#include<cstring>
#include<vector>
using namespace std;

#define FILENAME "stdFILE.txt" //���������ļ�����

//ѧ����(������)
class Student {
public:
    virtual void showInfo() = 0; //��ʾ������Ϣ
    // virtual ~Student() = 0;      //���崿������������֤�ͷŶ����ڴ�ʱ���ᷢ���ڴ�й©

    string StId;     //ѧ��
    string m_name;  //����
    string m_Dept;  //ְ��
};
//��ͨѧ����
class Nomalstuden : public Student {
public:
    Nomalstuden(string Id, string name, string dep);
    void showInfo(); //��ʾ������Ϣ
    // ~Nomalstuden() {
    //     delete this;
    // }
};
//�೤��
class ClassPresident : public Student {
public:
    ClassPresident(string Id, string name, string dep);
    void showInfo();
    // ~ClassPresident() {
    //     delete this;
    // }
};
//��ɲ���
class Classleader : public Student {
public:
    Classleader(string Id, string name, string dep);
    void showInfo();
    // ~Classleader() {
    //     delete this;
    // }
};

//����Ա��
class StudentManager {
public:
    StudentManager();//���캯��
    void Show_Menu(); //��ӡ�˵�����
    void Exit_System();//�˳�ϵͳ
    void Addinfo();    //����ѧ����Ϣ
    void save();       //��ѧ����Ϣ���浽�ļ���
    void init_Std();   //��ʼ��ѧ��
    void show_Std();   //��ʾѧ����Ϣ
    void del_Std();    //ɾ��ѧ����Ϣ
    void mod_Std();    //�޸�ѧ����Ϣ
    void find_Std();   //����ѧ����Ϣ
    void clean_File(); //����ļ�
    int IsExist(string id);     //�ж�ѧ��Ϊid��ѧ����Ϣ�Ƿ���ڣ������ظ�ѧ���±�
    ~StudentManager();//��������

    vector<Student*>* m_StdArray; //������ӵ�ѧ����Ϣ
    bool m_fileIsEmpty;     //����ļ��Ƿ�Ϊ��
};

//ѧ���ി���������ⲿʵ��
// Student :: ~Student() {
//     delete this;
// }

//����Ա����ʵ��
StudentManager::StudentManager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    //����ļ�������
    if (!ifs.is_open()) {
        cout << "���ļ������ڣ�" << endl;
        this->m_fileIsEmpty = true;
        this->m_StdArray = NULL;
        ifs.close();
        return;
    }
    //�ļ����ڵ�������Ϊ��
    char ch;
    ifs >> ch;       //�ȶ�ȡһ���ַ�
    if (ifs.eof()) {
        cout << "���ļ�Ϊ�գ�" << endl;
        this->m_fileIsEmpty = true;
        this->m_StdArray = NULL;
        ifs.close();
        return;
    }
    //�ļ����ڣ�����¼��ʼ����
    this->m_StdArray = new vector<Student*>;
    this->init_Std();
}
void StudentManager::Show_Menu() {
    cout << "-------------------------------------------" << endl;
    cout << "------------  ��ӭʹ��ѧ������ϵͳ�� ----------" << endl;
    cout << "-------------  0.�˳��������  -------------" << endl;
    cout << "-------------  1.����ѧ����Ϣ  -------------" << endl;
    cout << "-------------  2.��ʾѧ����Ϣ  -------------" << endl;
    cout << "-------------  3.ɾ��ѧ����Ϣ  -------------" << endl;
    cout << "-------------  4.�޸�ѧ����Ϣ  -------------" << endl;
    cout << "-------------  5.����ѧ����Ϣ  -------------" << endl;
    cout << "-------------  6.�����������  -------------" << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
}
void StudentManager::Exit_System() {
    cout << "��л����ʹ�ã�" << endl;
    // system("pause");
    exit(-1);  //�˳�ϵͳ
}
void StudentManager::Addinfo() {
    if (!this->m_StdArray)
        this->m_StdArray = new vector<Student*>;
    cout << "ѧ����Ϣ��ʼ¼��" << endl;
    int i = 1;
    while (true) {
        char flag;
        string id;
        string name;
        string dep;
        cout << "�������" << i << "��ѧ��ѧ�ţ�" << endl;
        cin >> id;
        cout << "�������" << i << "��ѧ��������" << endl;
        cin >> name;
        cout << "�������" << i << "��ѧ��ְλ��(�೤or��ɲ�or��ͨѧ��)" << endl;
        cin >> dep;
        Student* std = NULL;
        if (dep == "�೤") {
            std = new ClassPresident(id, name, dep);
        }
        else if (dep == "��ɲ�") {
            std = new Classleader(id, name, dep);
        }
        else if (dep == "��ͨѧ��") {
            std = new Nomalstuden(id, name, dep);
        }
        else {
            cout << "��ѧ��ְλ�����ڣ���Ϣ¼�������" << endl;
            break;
        }
        this->m_StdArray->push_back(std);
        i++;
        this->m_fileIsEmpty = false;   //�����ļ��ǿձ��
        cout << "�Ƿ����¼����Ϣ��(y����¼�룬n����¼��)" << endl;
        cin >> flag;
        if (flag == 'y') continue;
        else break;
    }
    cout << "�ɹ������" << i - 1 << "��ѧ����Ϣ!" << endl;
    this->save();
    system("pause");
    system("cls");
}
void StudentManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_StdArray->size(); ++i) {
        ofs << this->m_StdArray->at(i)->StId << " "
            << this->m_StdArray->at(i)->m_name << " "
            << this->m_StdArray->at(i)->m_Dept << endl;
    }
    ofs.close();
}
void StudentManager::init_Std() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    string id;
    string name;
    string dep;
    while (ifs >> id && ifs >> name && ifs >> dep) {
        Student* std = NULL;
        if (dep == "�೤") {
            std = new ClassPresident(id, name, dep);
        }
        else if (dep == "��ɲ�") {
            std = new Classleader(id, name, dep);
        }
        else if (dep == "��ͨѧ��") {
            std = new Nomalstuden(id, name, dep);
        }
        this->m_StdArray->push_back(std);
    }
    this->save();
}
void StudentManager::show_Std() {
    if (this->m_fileIsEmpty) {
        cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
    }
    else {
        for (int i = 0; i < this->m_StdArray->size(); ++i) {
            this->m_StdArray->at(i)->showInfo();
        }
    }
    system("pause");
    system("cls");
}
void StudentManager::del_Std() {
    if (this->m_fileIsEmpty) {
        cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
    }
    else {
        cout << "��������Ҫɾ����ѧ��ѧ�ţ�" << endl;
        string id;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1) {
            this->m_StdArray->erase(this->m_StdArray->begin() + index);
            this->save();
            cout << "ɾ���ɹ���" << endl;
        }
        else {
            cout << "ɾ��ʧ�ܣ������ڸ�ѧ�ŵ�ѧ����" << endl;
        }
    }
    system("pause");
}
int StudentManager::IsExist(string id) {
    int len = this->m_StdArray->size();
    int index = -1;
    for (int i = 0; i < len; ++i) {
        if (this->m_StdArray->at(i)->StId == id) {
            index = i;
            break;
        }
    }
    return index;
}
void StudentManager::mod_Std() {
    if (this->m_fileIsEmpty) {
        cout << "�ļ������ڻ����ļ�Ϊ��" << endl;
    }
    else {
        cout << "��������Ҫ�޸ĵ�ѧ��ѧ�ţ�" << endl;
        string id;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1) {
            //delete this -> m_StdArray -> at(index);
            string newid;
            string newname;
            string newdep;
            Student* std = NULL;
            cout << "������ѧ��Ϊ" << id << "��ѧ������������ѧ�ţ�" << endl;
            cin >> newid;
            cout << "��������������" << endl;
            cin >> newname;
            cout << "��������ְ��" << endl;
            cin >> newdep;
            if (newdep == "�೤") {
                std = new ClassPresident(newid, newname, newdep);
            }
            else if (newdep == "��ɲ�") {
                std = new Classleader(newid, newname, newdep);
            }
            else if (newdep == "��ͨѧ��") {
                std = new Nomalstuden(newid, newname, newdep);
            }
            this->m_StdArray->at(index) = std;
            cout << "�޸ĳɹ���" << endl;
            this->save();
        }
        else {
            cout << "�޸�ʧ�ܣ������ڸ�ѧ�ŵ�ѧ����" << endl;
        }
    }
    system("pause");
}
void StudentManager::find_Std() {
    if (this->m_fileIsEmpty) {
        cout << "�ļ������ڻ����ļ�Ϊ��" << endl;
    }
    else {
        cout << "��������Ҫ���ҵ�ѧ��ѧ�ţ�" << endl;
        string id;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1) {
            cout << "���ҳɹ�����ѧ����Ϣ���£�" << endl;
            this->m_StdArray->at(index)->showInfo();
        }
        else {
            cout << "����ʧ�ܣ���ѧ�������ڣ�" << endl;
        }
    }
}
void StudentManager::clean_File() {
    cout << "ȷ������������ݣ�" << endl;
    cout << "1,ȷ��" << endl;
    cout << "2,����" << endl;
    int selet = 0;
    cin >> selet;
    if (selet == 1) {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_StdArray) {
            this->m_StdArray->clear();
            vector<Student*>(*this->m_StdArray).swap(*this->m_StdArray);
            this->m_fileIsEmpty = true;
            this->m_StdArray = NULL;
        }
        cout << "��ճɹ���" << endl;
    }
    system("pause");
    system("cls");
}
StudentManager :: ~StudentManager() {
    if (this->m_StdArray) {
        this->m_StdArray->clear();
        delete[] this->m_StdArray;
        this->m_StdArray = NULL;
    }
}

//��ͨѧ������ʵ��
Nomalstuden::Nomalstuden(string Id, string name, string dep) {
    this->StId = Id;
    this->m_name = name;
    this->m_Dept = dep;
}
void Nomalstuden::showInfo() {
    cout << "ѧ��ѧ�ţ�" << this->StId
        << "\tѧ��������" << this->m_name
        << "\tѧ��ְλ��" << this->m_Dept
        << "\tѧ���������ذ༶����" << endl;
}

//�೤����ʵ��
ClassPresident::ClassPresident(string Id, string name, string dep) {
    this->StId = Id;
    this->m_name = name;
    this->m_Dept = dep;
}
void ClassPresident::showInfo() {
    cout << "ѧ��ѧ�ţ�" << this->StId
        << "\tѧ��������" << this->m_name
        << "\tѧ��ְλ��" << this->m_Dept
        << "\tѧ�����񣺹����ɲ����븨��Ա�Խӣ�����༶" << endl;
}

//��ɲ�����ʵ��
Classleader::Classleader(string Id, string name, string dep) {
    this->StId = Id;
    this->m_name = name;
    this->m_Dept = dep;
}
void Classleader::showInfo() {
    cout << "ѧ��ѧ�ţ�" << this->StId
        << "\tѧ��������" << this->m_name
        << "\tѧ��ְλ��" << this->m_Dept
        << "\tѧ�����������Լ���ְ�𣬺͸�����ʦ�Խӣ�����༶ѧ��" << endl;
}

//������
int main() {
    StudentManager stm;     //ʵ��������Ա
    int choice;             //�洢�û�ѡ��
    while (true) {
        stm.Show_Menu();    //���ô�ӡ�����Ա����
        cout << "����������ѡ��" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:             //�˳�ϵͳ
            stm.Exit_System();
            break;
        case 1:             //����ѧ��
            stm.Addinfo();
            break;
        case 2:             //��ʾѧ��
            stm.show_Std();
            break;
        case 3:             //ɾ��ѧ��
            stm.del_Std();
            break;
        case 4:             //�޸�ѧ��
            stm.mod_Std();
            break;
        case 5:             //����ѧ��
            stm.find_Std();
            break;
        case 6:             //����ĵ�
            stm.clean_File();
            break;
        default:
            system("cls");  //��������
            break;
        }
    }

    system("pause");
    return 0;
}
��������������������������������
��Ȩ����������ΪCSDN������YXXYX����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https ://blog.csdn.net/YXXXYX/article/details/119154840