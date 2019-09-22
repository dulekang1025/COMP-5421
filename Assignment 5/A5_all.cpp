//
// Created by Lekang Du on 2019-08-12.
//


#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
bool is_palindrome(const std::string & phrase);

// 1
void test_is_palindrome() {
    std::string str_i = std::string("Was it a car or a cat I saw?");
    std::string str_u = std::string("Was it a car or a cat U saw?");
    cout << "the phrase \"" + str_i + "\" is " +
            (is_palindrome(str_i) ? "" : "not ") + "a palindrome\n";
    cout << "the phrase \"" + str_u + "\" is " +
            (is_palindrome(str_u) ? "" : "not ") + "a palindrome\n";
}

struct Predict{
    bool operator()(char ch){
        if(isalpha(ch)==0) return true;
        else return false;
    }
};
bool myPredictor(char c){
    if(isalpha(c)==0) return true;
    else return false;
}
string toupperCase(string temp) {
    std::transform(temp.begin(), temp.end(),temp.begin(),[](char ch){ return toupper(ch); });
    return std::move(temp);
}

bool is_palindrome(const std::string & phrase){
    Predict pred;
    string temp;
    //1. use std::remove_copy_if to move only alphabet characters from phrase to
    //temp; note that temp is empty; hence the need for an inserter iterator
    //remove_copy_if(phrase.begin(),phrase.end(),insert_iterator<string >(temp, temp.begin()),myPredictor);
    remove_copy_if(phrase.begin(),phrase.end(),insert_iterator<string >(temp, temp.begin()),pred);

    //2. use std::transform to convert all characters in temp to uppercase (or lowercase)
    // (see page 22, Smart Pointers + Move Semantics, Moodle)
    temp = toupperCase(temp);

    //3. use std::equal to compare the first half of temp with its second half,
    // moving forward in the first half (starting at temp.begin())
    // and moving backward in the second half (starting at temp.rbegin())
    bool r = std::equal(temp.begin(),temp.end(),temp.rbegin());
    //4. return the outcome of step 3
    return r;
}

// 2
template <typename Iterato > // template header
std::pair<Iterato,bool>
second_max(Iterato start, Iterato finish) // function template return type // function signature
{
    int count = 0;
    auto result = *start;
    auto s1 = start;
    auto f1 = finish;
    bool f = false;
    while(start != finish){
        if(*start != *(finish-1)){
            f = true;
            break;
        }
        ++start;
    }

    start = s1;
    finish = f1;

    while(start != finish){
        count++;
        ++start;
    }
    start = s1;
    finish = f1;

    if(start == finish) return std::make_pair(finish, false);
    else if(!f){
        return std::make_pair(start, false);
    }
    else if(count == 1) return std::make_pair(start, false);
    else{
        // 1, find the largest
        // 2, find the second largest in the rest elements
        auto res1 = *start;
        while(start != finish){
            if(*start > res1){
                res1 = *start;
            }
            ++start;
        }
        start = s1;
        finish = f1;
        Iterato res2_it = finish;
        while(start != finish){
            if(*start < res1){
                res2_it = start;
                break;
            }
            ++start;
        }
        start = s1;
        finish = f1;
        auto res2 = *res2_it;
        auto r = res2_it;
        while(start != finish){
            if(*start > res2 && *start != res1){
                res2 = *start;
                r = start;
            }
            ++start;
        }
        start = s1;
        finish = f1;
        return make_pair(r,true);
    }
}


void test_second_max(std::vector<int> vec) {
// note: auto in the following statement is deduced as
// std::pair<std::vector<int>::iterator, bool>
    auto retval = second_max(vec.begin(), vec.end());
    if (retval.second)
    {
        cout << "The second largest element in vec is " << *retval.first << endl;
    }
    else
    {
        if (retval.first == vec.end())
            cout << "List empty , no elements\n";
        else
            cout << "Container’s elements are all equal to "
                 << *retval.first << endl;
    }
}

// 3
struct Functor{
    int nf;
    Functor(int n){
        nf = n;
    }
    bool operator()(string s){
        return (s.length() == nf);
    }
};
bool precdict(string s , int n){
    return (s.length() == n);
}

int freeFunc_countStrings(vector<std::string> &v, int n){
    return count_if(v.begin(),v.end(),bind(precdict, placeholders::_1,n));
}

int countStringLambda(vector<std::string> &v, int n){
    return count_if(v.begin(),v.end(),[n](string s){ return (s.length() == n);});
}

int countStringFreeFun(vector<std::string> &v, int n){
    return freeFunc_countStrings(v, n);
}

int countStringFunctor(vector<std::string> &v, int n){
    Functor functor(n);
    return count_if(v.begin(),v.end(),functor);
}

//4
void charFrequency(){
    cout<<"Enter one or more lines of text."<<endl;
    cout<<"To end input press Ctrl - Z in Windows and Ctrl - D in Linux"<<endl;
    map<char, int> m;
    //string temp;
    //vector<char> v;
    istream_iterator<char> is(cin);
    istream_iterator<char> eof;
    for_each(is,eof,[&m](const char c){if(!isspace(c)) m[c] =+ 1;});
    //copy(is,eof,temp);
    map<char,int>::iterator it;
    for(it = m.begin();it != m.end(); ++it){
        cout<<"?"<<endl;
        cout<<it->first<<" "<<it->second<<endl;
    }

}

// 5
struct compare{
    bool operator() (const string &x,const string &y){
        if (x.length() < y.length()) return true;
        else if (x.length() > y.length()) return false;
        else{
            for (size_t i = 0; i < x.length(); i++) {
                if (x.at(i) < y.at(i)) return true;
            }
        }
    }
};
//bool compare(const string &x,const string &y){
//    if (x.length() < y.length()) return true;
//    else if (x.length() > y.length()) return false;
//    else{
//        for (size_t i = 0; i < x.length(); i++) {
//            if (x.at(i) < y.at(i)) return true;
//        }
//    }
//}

void multisetUsingMyComparator(){
    std::multiset <std::string,compare> strSet; // an empty set
    // a set that uses the default std::less<int> to sort the set elements
    std::vector <std::string > vec {"C", "BB", "A", "CC", "A", "B","BB", "A", "D", "CC", "DDD", "AAA"};
    copy(vec.begin(),vec.end(),inserter(strSet,strSet.begin()));
    std::ostream_iterator<std::string> out(cout, " ");
    std::copy(strSet.begin(), strSet.end(), out);
}
int main(){
    // problem 1:
    test_is_palindrome();
    cout << "\n";
    // problem 2:
    std::vector<int> v1{ 1 }; // one element
    test_second_max(v1);
    std::vector<int> v2{ 1, 1 }; // all elements equal
    test_second_max(v2);
    std::vector<int> v3{ 1, 1, 3, 3, 7, 7}; // at least with two distict elements
    test_second_max(v3);
    std::vector<int> v4{ 10,5,10}; // at least with two distict elements
    test_second_max(v4);
    cout << "\n";
// problem 3:
    std::vector <std::string > vecstr
    { "count_if", "Returns", "the", "number", "of", "elements", "in", "the",
      "range", "[first", "last)", "for", "which", "pred", "is", "true."
    };
    cout << countStringLambda(vecstr , 5) << endl;
    cout << countStringFreeFun(vecstr , 5) << endl;
    cout << countStringFunctor(vecstr , 5) << endl;
    cout << "\n";
// problem 4:
 //charFrequency();
    cout << "\n";
// problem 5:
 multisetUsingMyComparator();
 cout << "\n";
}