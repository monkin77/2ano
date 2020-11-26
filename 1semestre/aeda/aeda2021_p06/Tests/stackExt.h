# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> stack;
    ::stack<T> minStack;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const{
    return stack.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top(){
    T *novo = new T();
    *novo = stack.top();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop(){
    std::stack<T> auxStack;
    if( stack.top() == minStack.top() ){
        minStack.pop();
    }
    else{
        int minSize = minStack.size();
        for(int i = 0; i < minSize; i++){       //aux Stack has the original stack inverted without the removed element
            if( stack.top() == minStack.top() ){
                minStack.pop();
                break;
            }
            else{
                auxStack.push(minStack.top());
                minStack.pop();
            }
        }
    }
    int auxSize = auxStack.size();
    for(int i = 0; i < auxSize; i++){       // inverts back the minStack
        minStack.push(auxStack.top());
        auxStack.pop();
    }

    stack.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val){
    stack.push(val);
    std::stack<T> auxStack;
    bool isInserted = false;
    if(minStack.empty())
        minStack.push(val);
    else{
        int minSize = minStack.size();
        for(int i = 0; i < minSize; i++){       // no fim deste loop temos a stack ordenada por ordem decrescente (temos de inverter)
            if(isInserted){
                auxStack.push(minStack.top());
                minStack.pop();
            }
            else{
                if( minStack.top() <= val ){         // se o valor atual na stack for menor que o novo, continuar a descer
                    auxStack.push(minStack.top());
                    minStack.pop();
                }
                else{                               // se o valor atual na stack for maior que o novo, colocar o novo em cima(pois no fim vai ser invertida)
                    auxStack.push(val);
                    auxStack.push(minStack.top());
                    minStack.pop();
                    isInserted = true;
                }
            }
        }
        if(!isInserted)             //if value is bigger than all others
            auxStack.push(val);
        int auxSize = auxStack.size();
        for(int i = 0; i < auxSize; i++){
            minStack.push(auxStack.top());
            auxStack.pop();
        }
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin(){
    T *novo = new T();
    *novo = minStack.top();
    return *novo;
}

