#include <iostream>
#include <string>
#include <fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

int p1Health=8000, p2Health=8000;
int round = 1;

//Queue Class
class DynIntQueue
{
    private:
       // Structure for the queue nodes
       struct QueueNode
       {
          string name; // Value in a node
          int attack;
          int defense;
          char type;
          QueueNode *next; // Pointer to the next node
       };

       QueueNode *front;  // The front of the queue
       QueueNode *rear;   // The rear of the queue
       int numItems;      // Number of items in the queue
    public:
       // Constructor
       DynIntQueue()
        {
           front = nullptr;
           rear = nullptr;
           numItems = 0;
        }

       // Destructor
       ~DynIntQueue()
         {
            clear();
         }

       // Queue operations
        void enqueue(string na, int att, int def, char ty)
        {
            QueueNode *newNode = nullptr;

            // Create a new node and store num there.
            newNode = new QueueNode;
            newNode->name = na;
            newNode->attack=att;
            newNode->defense=def;
            newNode->type=ty;
            newNode->next = nullptr;

            // Adjust front and rear as necessary.
            if (isEmpty())
            {
                front = newNode;
                rear = newNode;
            }
            else
            {
                rear->next = newNode;
                rear = newNode;
            }

            // Update numItems.
            numItems++;
        }
        void dequeue(string &na, int &att, int &def, char &ty)
        {
            QueueNode *temp = nullptr;

            if (isEmpty())
            {
                //?
            }
            else
            {
                //Saves all card's data
                na = front->name;
                att = front->attack;
                def = front->defense;
                ty = front->type;

                // Remove the front node and delete it.
                temp = front;
                front = front->next;
                delete temp;

                // Update numItems.
                numItems--;
            }
        }   
       bool isEmpty()
       {
            bool status;
            if (numItems>0)
                status=false;
            else
                status=true;
            return status;
       }
       // bool isFull() const;
       void clear()
       {
           //Temp variables
           string n;
           int a, d;
           char t;
           
           while (!isEmpty())
           {
               dequeue(n,a,d,t);
               cout << "Clearing deck" << endl;
           }
       }

       void display()
       {
            QueueNode *traverseNode;
            traverseNode=front;

            while (traverseNode!=nullptr)
            {
                string n;
                int a, d;
                char t;
                cout << traverseNode->name << " " << traverseNode->attack << " " << traverseNode->defense << " " << traverseNode->type << endl;
                traverseNode=traverseNode->next;
            }
       }
    void tradeCard(string &na, int &att, int &def, char &typ, bool &status)
       {
            QueueNode *nodePtr=nullptr, *previousNode=nullptr;
            status=false;
            
            if(!front)
            {
                return;
            }
            if (front->name==na)
            {
                nodePtr=front->next;
                na=front->name;
                att=front->attack;
                def=front->defense;
                typ=front->type;
                delete front;
                front=nodePtr;
                numItems--;
                status=true;
            }
            else
            {
                nodePtr=front;

                while (nodePtr!=nullptr && nodePtr->name!=na)
                {
                    previousNode=nodePtr;
                    nodePtr=nodePtr->next;
                }
                if (nodePtr)
                {
                    previousNode->next=nodePtr->next;
                    na=nodePtr->name;
                    att=nodePtr->attack;
                    def=nodePtr->defense;
                    typ=nodePtr->type;
                    delete nodePtr;
                    numItems--;
                    status=true;
                }
            }
       }
};

//Linked List Class for hand
class Hand
{
    private:
        struct ListNode
        {
            string name;
            int attack, defense;
            char type;
            struct ListNode *next;
        };
        ListNode *head;
        int numItems;
    public:
        //Constructor
        Hand()
        {
            head=nullptr;
            numItems=0;
        }
        //Destructor
        ~Hand ()
        {
            clear();
        }
        void appendNode(string na, int att, int def, char typ)
        {
            ListNode *newNode;
            ListNode *nodePtr;
            
            newNode=new ListNode;
            newNode->name=na;
            newNode->attack=att;
            newNode->defense=def;
            newNode->type=typ;
            newNode->next=nullptr;
            
            if(!head)
                head=newNode;
            else
            {
                nodePtr=head;
                while(nodePtr->next)
                        nodePtr=nodePtr->next;
                
                nodePtr->next=newNode;
            }
            numItems++;
        }
        void displayList() const
        {
            ListNode *nodePtr;
            nodePtr=head;
            while (nodePtr)
            {
                cout << nodePtr->name << ": " << nodePtr->attack << " (attack) " << nodePtr->defense << " (defense) " << nodePtr->type;
                if (nodePtr->type=='a')
                {
                    cout << " (type: +800 attack)" << endl;
                }
                else
                    cout << " (type: +400 defense)" << endl;
                nodePtr=nodePtr->next;
            }
        }
        
            void deleteNode(string &na, int &att, int &def, char &typ, bool &status)
            {   
                ListNode *nodePtr;
                ListNode *previousNode;
                
                //Intiialize status to false
                status=false;
                    
                if (!head)
                {
                    return;
                }
                if (head->name==na)
                {
                    nodePtr=head->next;
                    na=head->name;
                    att=head->attack;
                    def=head->defense;
                    typ=head->type;
                    delete head;
                    head=nodePtr;
                    numItems--;
                    status=true;
                    
                }
                else
                {
                    nodePtr=head;
                    
                    while (nodePtr!=nullptr && nodePtr->name!=na)
                    {
                        previousNode=nodePtr;
                        nodePtr=nodePtr->next;
                    }
                    
                    if (nodePtr)
                    {
                        previousNode->next=nodePtr->next;
                        na=nodePtr->name;
                        att=nodePtr->attack;
                        def=nodePtr->defense;
                        typ=nodePtr->type;
                        delete nodePtr;
                        numItems--;
                        status=true;
                    }
                }
            }
    bool isEmpty()
    {
        bool status;
        if(numItems>0)
            status=false;
        else
            status=true;
        return status;
    }
    void clear()
    {
        //Temp variables
        string n;
        int a, d;
        char t;
        bool f;
        ListNode *nodePtr;
        nodePtr=head;
        
        while (nodePtr!=nullptr)
        {
            cout << "Clearing Hand" << endl;
            nodePtr=nodePtr->next;
            delete head;
            head=nodePtr;
        }
    }
};

void makeDecks (DynIntQueue&, DynIntQueue&);
void battle (string, string, DynIntQueue&, DynIntQueue&, Hand&, Hand&);
void determineWinner(string, string, DynIntQueue&, DynIntQueue&, Hand&, Hand&, DynIntQueue& , DynIntQueue&, DynIntQueue&, DynIntQueue&);
void drawFive(DynIntQueue&, DynIntQueue&, Hand&, Hand&);
void tradeCards(string, string, DynIntQueue&, DynIntQueue&, Hand&, Hand&);
void replay(DynIntQueue&, DynIntQueue&, Hand&, Hand&, string, string, DynIntQueue&, DynIntQueue&, DynIntQueue&, DynIntQueue&);

void p1attp2att(string, string, int, int, char, char, DynIntQueue&, DynIntQueue&, Hand&, Hand&, DynIntQueue&, DynIntQueue&, DynIntQueue&, DynIntQueue&);
void p1attp2def(string, string, int, int, char, char, DynIntQueue&, DynIntQueue&, Hand&, Hand&, DynIntQueue&, DynIntQueue&, DynIntQueue&, DynIntQueue&);
void p1defp2att(string, string, int, int, char, char, DynIntQueue&, DynIntQueue&, Hand&, Hand&, DynIntQueue&, DynIntQueue&, DynIntQueue&, DynIntQueue&);
void p1defp2def(string, string, int, int, char, char, DynIntQueue&, DynIntQueue&, Hand&, Hand&);

    
int main()
{
    //Create the decks
    
    DynIntQueue deck1, deck2;
    /*
    //Temp variables for each part of the card
    string na;
    int att, def;
    char typ;
    fstream d1, d2;
    //Open file for deck 1
    d1.open("deck.txt", ios::in);
    //Enqueue every card from file into deck 1
    while (d1 >> na >> att >> def >> typ)
    {
        deck1.enqueue(na, att, def, typ);
    }
    //Close file to reset for deck 2
    d1.close();
    //Open file for deck 2
    d2.open("deck.txt", ios::in);
    //Enqueue every card from file into deck 2
    while (d2 >> na >> att >> def >> typ)
    {
        deck2.enqueue(na, att, def, typ);
    }
    //Close file
    d2.close();
    */
    makeDecks(deck1, deck2);
    //Create hand linked lists
    Hand p1hand, p2hand;
    
    //Menu
    cout << "Welcome to Yu-gi-oh!"<<endl << endl;
    cout << "Choose and option from the following: " << endl;
    int choice;
    //Variables for player names (default is player 1 and player 2
    string name1="Player 1", name2="Player 2";
    
    //Display menu for the first time
    cout << endl << "1. Create Players" << endl << "2. Trade Cards with Other Player " << endl << "3. Battle other Player " << endl << "4. Display Decks ";
    cout << endl << endl << "Input: ";
    cin >> choice;
    //Redo menu until battle is chosen
    while (choice!= 3)
    {
        if ( choice == 1)
        {
            //Set names for each player
            cout << "Enter player 1 name: ";
            cin >> name1;
            cout << "Enter player 2 name: ";
            cin >> name2;
        }
        else if (choice == 2)
        {
            cout << name1 << "'s Deck: " << endl;
            deck1.display();
            cout << endl << name2 << "'s Deck: " << endl;
            deck2.display();
            cout << endl;
            tradeCards(name1, name2, deck1, deck2, p1hand, p2hand);
        }
        else if (choice == 4)
        {
            cout << name1 << "'s Deck :" << endl;
            deck1.display();
            cout << endl;
            cout << name2 << "'s Deck :" << endl;
            deck2.display();
        }
        
         cout << endl << "1. Create Players" << endl << "2. Trade Cards with Other Player " << endl << "3. Battle other Player " << endl << "4. Display Decks ";
        cout << endl << endl << "Input :"; 
        cin >> choice;
     }
    
     if (choice == 3)
        {
            //Battle
              cout << endl << name1 << " will choose first." << endl;
              drawFive(deck1, deck2, p1hand, p2hand);
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
        }
    

     return 0;   
}

void makeDecks(DynIntQueue &deck1, DynIntQueue &deck2)
{
    //Temp variables
    string na;
    int att, def;
    char typ;
    fstream d1, d2;
    //Open file for deck 1
    d1.open("deck.txt", ios::in);
    //Enqueue every card from file into deck 1
    while (d1 >> na >> att >> def >> typ)
    {
        deck1.enqueue(na, att, def, typ);
    }
    //Close file to reset for deck 2
    d1.close();
    //Open file for deck 2
    d2.open("deck.txt", ios::in);
    //Enqueue every card from file into deck 2
    while (d2 >> na >> att >> def >> typ)
    {
        deck2.enqueue(na, att, def, typ);
    }
    //Close file
    d2.close();
}
    

void drawFive(DynIntQueue &deck1, DynIntQueue &deck2, Hand &hand1, Hand &hand2)
{
    //Temporary variables
    string n;
    int a, d;
    char t;
    //Draw for player 1
    for (int i=0; i<5; i++)
    {
        deck1.dequeue(n,a,d,t);
        hand1.appendNode(n,a,d,t);
    }
    //Draw for player 2
    for (int i=0; i<5; i++)
    {
        deck2.dequeue(n,a,d,t);
        hand2.appendNode(n,a,d,t);
    }
}

//Calls functions to update points for 4 possilbe outcomes of battle 

void battle (string name1, string name2, DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand)
{
    //Creating the queues for players' attack and defense
    DynIntQueue p1attack, p1defense, p2attack, p2defense;
    
    /*Moved this to main for scope of drawFive
    //Creating linked list for hand to queue
    Hand p1hand, p2hand;
    */
    cout << "Round " << round << ": " << endl << endl;
       round++;
    //temporary variables to store info
    string tempName;
    int tempAttack, tempDefense;
    char tempType;
    
    //status variable for card input checking
    bool found=false;
    
    int choiceActivate;
    string choiceCard;
   
    
    string tempAtt;
        //PLAYER 1
        //Show hand here
        cout << name1 << "'s hand: " << endl;
        p1hand.displayList();
        
        while (found!=true)
        {
            cout << endl << name1 << ": choose a card to put in the attack queue: " << endl;
            cin >> choiceCard;
            p1hand.deleteNode(choiceCard, tempAttack, tempDefense, tempType, found);
        }
        
        //Resetting found to false for next input
        found=false;

        //Put card in attack queue
        p1attack.enqueue(choiceCard, tempAttack, tempDefense, tempType);
        
        while (found!= true)
        {
            cout << name1 << ": choose a card to put in the defense queue: " << endl;
            cin >> choiceCard;
            p1hand.deleteNode(choiceCard, tempAttack, tempDefense, tempType, found);
        }
        
        //Put card in defense queue
        p1defense.enqueue(choiceCard, tempAttack, tempDefense, tempType);
        
        cout << name1 << ": which would you like to activate? Enter 1 for attack or 2 for defense: ";
        cin >> choiceActivate;
        cout << endl;
        
/*        if (choiceActivate == 1)
        {
            p1attack.dequeue(tempName, tempAttack, tempDefense, tempType);
            //Put card into battlefield
        }
        else
        {
            p1defense.dequeue(tempName, tempAttack, tempDefense, tempType);
            //Put card into battlefield
        }*/
    
        //Draw 2 for player 1
        for (int i=0; i<2; i++)
        {
            string drawN;
            int drawA, drawD;
            char drawT;
            deck1.dequeue(drawN, drawA, drawD, drawT);
            p1hand.appendNode(drawN, drawA, drawD, drawT);
        }
        
        //PLAYER 2
        //Show hand here
    string tempName2;
    int tempAttack2, tempDefense2;
    char tempType2;
        
        
    int choiceActivate2;
    string choiceCard2;
        cout << name2 << "'s hand: " << endl;
        p2hand.displayList();
    
        //Resetting found to false for next input
        found=false;
        
        while (found!=true)
        {
            cout << endl << name2 << ": choose a card to put in the attack queue: " << endl;
            cin >> choiceCard2;
            p2hand.deleteNode(choiceCard2, tempAttack2, tempDefense2, tempType2, found);
        }
        
        //Put card in attack queue
        p2attack.enqueue(choiceCard2, tempAttack2, tempDefense2, tempType2);
        
        
        //Resetting found to fales for next input
        found=false;
        //Looking for card and 
        while (found!=true)
        {
            cout << name2 << ": choose a card to put in the defense queue: " << endl;
            cin >> choiceCard2;
            p2hand.deleteNode(choiceCard2, tempAttack2, tempDefense2, tempType2, found);
        }
        
        //Put card in defense queue
        p2defense.enqueue(choiceCard2, tempAttack2, tempDefense2, tempType2);
        
        cout << name2 << ": which would you like to activate? Enter 1 for attack or 2 for defense: ";
        cin >> choiceActivate2;
        cout << endl;
    
        //Draw 2 for player 2
        for (int i=0; i<2; i++)
        {
            string drawN;
            int drawA, drawD;
            char drawT;
            deck2.dequeue(drawN, drawA, drawD, drawT);
            p2hand.appendNode(drawN, drawA, drawD, drawT);
        }
        
        if (choiceActivate2 == 1)
        {
            //Put card into battlefield
            if (choiceActivate == 1) //player one also attacks
            {
                p1attack.dequeue(tempName, tempAttack, tempDefense, tempType);
                p2attack.dequeue(tempName2, tempAttack2, tempDefense2, tempType2);
                p1attp2att(name1, name2, tempAttack, tempAttack2, tempType, tempType2, deck1, deck2, p1hand, p2hand, p1attack, p2attack, p1defense, p2defense);
            }
            else if (choiceActivate == 2) //player one defends
            {
                p1defense.dequeue(tempName, tempAttack, tempDefense, tempType);
                p2attack.dequeue(tempName2, tempAttack2, tempDefense2, tempType2);
                p1defp2att(name1, name2, tempDefense, tempAttack2, tempType, tempType2, deck1, deck2, p1hand, p2hand, p1attack, p2attack, p1defense, p2defense);
            }
            else 
                cout << "error in comparing scores" << endl;
              
        }
        else
        {
            //Put card into battlefield
            if (choiceActivate == 1)
            {
                p1attack.dequeue(tempName, tempAttack, tempDefense, tempType);
                p2defense.dequeue(tempName2, tempAttack2, tempDefense2, tempType2);
                p1attp2def(name1, name2, tempAttack, tempDefense2, tempType, tempType2, deck1, deck2, p1hand, p2hand, p1attack, p2attack, p1defense, p2defense);
            }
            else if (choiceActivate ==2)
            {
                p1defense.dequeue(tempName, tempAttack, tempDefense, tempType);
                p2defense.dequeue(tempName2, tempAttack2, tempDefense2, tempType2);
                p1defp2def(name1, name2, tempDefense, tempDefense2, tempType, tempType2, deck1, deck2, p1hand, p2hand);
            }
            else
                cout << "Error in comparing cards" << endl;
        } 
}

//four functions for the four options of play

//outcome #1. Both players activate attack cards. only call after player 2 activates
void p1attp2att (string name1, string name2, int p1Value, int p2Value, char p1Type, char p2Type, DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand, DynIntQueue &p1att, DynIntQueue &p2att, DynIntQueue &p1def, DynIntQueue &p2def)
{
   if (p1Type == 'A' || p1Type == 'a')
        p1Value = p1Value + 800;
    if (p2Type == 'A'|| p1Type == 'a')
        p2Value = p2Value + 800;
    
        if (p1Value > p2Value)
        {
            p2Health =  p2Health - p1Value;
            cout << endl << name1 << " played a stronger card and won this round. Player 2 will lose life points." << endl;
            determineWinner(name1, name2, deck1, deck2, p1hand, p2hand, p1att, p2att, p1def, p2def); //check to see if game is over
             cout << name1 << ";s life points: " << p1Health << "       " << name2 << "'s life points: " << p2Health << endl << endl;
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
        }
        else if (p2Value > p1Value)
        {
            p1Health = p1Health - p2Value;
            cout << endl << name2 << " played a stronger card and won this round." << name1 << " will lose life points." << endl;
            determineWinner(name1, name2, deck1, deck2, p1hand, p2hand, p1att, p2att, p1def, p2def);
            cout << name1 << "'s life points: " << p1Health << "       " << name2 << "'s life points: " << p2Health << endl << endl;
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
        }
        else
        { 
            cout << "The cards played were of the same value and health points remain unchanged. Next round." << endl;
            cout << name1 << "'s life points: " << p1Health << "      " << name2 << "'s life points: " << p2Health << endl << endl;
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
        }   
}

//outcome #2 - Player 1 Defends, Player 2 attacks
void p1defp2att (string name1, string name2, int p1Value, int p2Value, char p1Type, char p2Type,  DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand, DynIntQueue &p1att, DynIntQueue &p2att, DynIntQueue &p1def, DynIntQueue &p2def)
{
    if ( p1Type == 'B' || p1Type == 'b')
        p1Value = p1Value + 400;
    if ( p2Type == 'A' || p2Type == 'a')
        p2Value = p2Value + 800;
    
    if (p1Value >= p2Value)
    {
        cout << name1 << " has sucessfully defended against " << name2 << "'s attack!" << endl;
        cout << name1 << "'s life points: " << p1Health << "    " << name2 << "'s life points: " << p2Health << endl << endl;
     battle(name1, name2, deck1, deck2, p1hand, p2hand);
    }
    else //if (p2Value > p1Value)
    {
        cout << name1 << "'s defense was no match for " << name2 << "'s attack." << endl;
        int diff;
        diff = p2Value - p1Value;
        p1Health = p1Health - diff;
        //check to see if still alive
        determineWinner(name1, name2, deck1, deck2, p1hand, p2hand, p1att, p2att, p1def, p2def);
        cout << name1 << "'s life points: " << p1Health << "    " << name2 << "'s life points: " << p2Health << endl << endl;
         battle(name1, name2, deck1, deck2, p1hand, p2hand);
    }
    
}

//Outcome #3 - Player 1 attacks, Player 2 defends
void p1attp2def (string name1, string name2, int p1Value, int p2Value, char p1Type, char p2Type,  DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand, DynIntQueue &p1att, DynIntQueue &p2att, DynIntQueue &p1def, DynIntQueue &p2def)
{
    if (p1Type == 'A' || p1Type == 'a')
        p1Value = p1Value + 800;
    if (p2Type == 'B' || p2Type == 'b')
        p2Value = p2Value + 400;
    
    if (p2Value >= p1Value)
    {
        cout << name2 << " has sucessfully defended against " << name2 << "'s attack!" << endl;
        determineWinner(name1, name2, deck1, deck2, p1hand, p2hand, p1att, p2att, p1def, p2def); //check to see if game is over
                 cout << name1 << "'s life points: " << p1Health << "    " << name2 << "'s life points: " << p2Health << endl << endl;
            
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
    }
    else //if (p1Value > p2Value)
    {
        cout << name2 << "'s defense was no match for " << name1 << "'s attack." << endl;
        
        int diff;
        diff = p1Value - p2Value;
        p2Health = p2Health - diff;
        //check to see if they are still alive
        determineWinner(name1, name2, deck1, deck2, p1hand, p2hand, p1att, p2att, p1def, p2def);
         cout << name1 << "'s life points: " << p1Health << "    " << name2 << "'s life points: " << p2Health << endl << endl;
            
             battle(name1, name2, deck1, deck2, p1hand, p2hand);
    }
    
}   

//outcome #4 - Both players defended
void p1defp2def (string name1, string name2, int p1Value, int p2Value, char p1Type, char p2Type, DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand )
{
    cout << "Both players have chosen to defend. We will move onto the next round." << endl;
       cout << name1 << "'s life points: " << p1Health << "    " << name2 << "'s life points: " << p2Health << endl << endl;
    //cards discarded 
        
        battle(name1, name2, deck1, deck2, p1hand, p2hand);
}




void determineWinner(string name1, string name2, DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand, DynIntQueue &p1att, DynIntQueue &p2att, DynIntQueue &p1def, DynIntQueue &p2def) // call in each turn to check life points
{

    if ( p1Health <= 0 )
    {
        cout << "Congrats " << name2 << " you beat " << name1 << "!" << endl << "Game is over." << endl;
        replay(deck1, deck2, p1hand, p2hand, name1, name2, p1att, p2att, p1def, p2def);
                //exit(0);
    }
               
    
    if ( p2Health <= 0)
    {
        cout << "Congrats " << name1 << " you beat " << name2 << "!" << endl << "Game is over."  << endl;
        replay(deck1, deck2, p1hand, p2hand, name1, name2, p1att, p2att, p1def, p2def);
                //exit(0); 
    }
}


//attempt 1 
void tradeCards(string name1, string name2, DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand)
{
    string cardGive; //card that they offer to the other person
    string cardName; //card that the player wants from the other person
    
    //temporary variables to store info
    string tempNameGive, tempNameName;
    int tempAttackGive, tempDefenseGive, tempAttackName, tempDefenseName;
    char tempTypeGive, tempTypeName;
    
    //status variable for card input checking
    bool foundGive=false, foundName=false;
    //while (found != true)
    
    cout << endl << name1 << ": " << endl << "Which card would you like to offer?: ";
        cin >> cardName;
    
    cout << endl << name2 << ": " << endl << "Which card would you like to offer?: ";
        cin >> cardGive;
    
        cout << endl << name2 << " would you be willing to give " << name1 << " your " << cardName << " for their " << cardGive << " ? ";
        cout << endl << " Enter Y for yes or N for No : ";
            char choice;
        cin >> choice;
    
            if (choice == 'Y' || choice == 'y')
            {
                cout << " The trade will take place! " << endl;
                
                while (foundName==false)
                {
                    deck1.tradeCard(cardName, tempAttackName, tempDefenseName, tempTypeName, foundName);
                    
                    
                    if (foundName==false)
                    {
                        cout << "Could not find card " << name1 << " offered. Please re-enter: ";
                        cin >> cardName;
                    }
                }
                while (foundGive==false)
                {
                    deck2.tradeCard(cardGive, tempAttackGive, tempDefenseGive, tempTypeGive, foundGive);
                    if (foundGive==false)
                    {
                        cout << "Could not find card " << name2 << " offered. Please re-enter: ";
                        cin >> cardGive;
                    }
                }
                deck2.enqueue(cardName, tempAttackName, tempDefenseName, tempTypeName);
                deck1.enqueue(cardGive, tempAttackGive, tempDefenseGive, tempTypeGive);
            }
    
            if (choice == 'N' || choice == 'n')
            {
                cout << endl << name2 << " did not accept the trade offer. "<< endl;
            
            }
    
   /*
     cout << endl << name2 << ": " << endl << "Which card would you like from " << name1 << " ? :";
        cin >> cardName;
    
    cout << "Which card would you like to give to " << name1 << " ? : ";
        cin >> cardGive;
    
        cout << endl << name1 << " would you be willing to give " << name2 << " your " << cardName << " for their " << cardGive << " ? ";
        cout << endl << " Enter Y for yes or N for No : ";
            
        cin >> choice;
    
            if (choice == 'Y' || choice == 'y')
            {
                cout << " The trade will take place! " << endl;
                deck2.dequeue(cardGive, tempAttack, tempDefense, tempType);
                deck1.enqueue(cardGive, tempAttack, tempDefense, tempType);
                
                deck1.dequeue(cardName, tempAttack, tempDefense, tempType);
                deck2.enqueue(cardName, tempAttack, tempDefense, tempType);
            }
    
            if (choice == 'N' || choice == 'n')
            {
                cout << name1 << " did not accept the trade offer.";
            
            }
            */
    
    char again;
    cout << endl << "Would you like to trade again? Enter Y for yes or N for no :";
    cin >> again;
            while (again != 'Y' && again!='N' && again != 'y' && again != 'n')
            {
            cout << "That was not a valid entry, please re-enter: ";
            cin >> again;
            }
    
        if (again == 'Y' || again == 'y')
            tradeCards(name1, name2, deck1, deck2, p1hand, p2hand);
           
}

void replay(DynIntQueue &deck1, DynIntQueue &deck2, Hand &p1hand, Hand &p2hand, string name1, string name2, DynIntQueue &p1att, DynIntQueue &p2att, DynIntQueue &p1def, DynIntQueue &p2def)
{
    int replayChoice;
    cout << "Do you want to replay? (enter 1 for yes or 2 to quit): ";
    cin >> replayChoice;
    while (replayChoice<1 || replayChoice>2)
    {
        cout << "Not a valid entry. Please re-enter 1 or 2: ";
        cin >> replayChoice;
    }
    //Create fstream files
    //fstream deck1, deck2;
    if (replayChoice==1)
    {
        //Clear deck, hand, att, and def queues/lists
        deck1.clear();
        deck2.clear();
        p1hand.clear();
        p2hand.clear();
        p1att.clear();
        p2att.clear();
        p2att.clear();
        p2def.clear();

        makeDecks(deck1, deck2);
        deck1.display();
        cout << "AAAAAAAA" << endl;
        deck2.display();
        
        
        /*
        deck1.open("deck.txt", ios::in);
        //Temp variables
        string n;
        int a, d;
        char t;
        while (deck1 >> n >> a >> d >> t)
        */

        drawFive(deck1, deck2, p1hand, p2hand);
        battle(name1, name2, deck1, deck2, p1hand, p2hand);
    }
        else
            return;
    
}
