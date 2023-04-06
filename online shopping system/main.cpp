#include <iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<map>
using namespace std;
class Item
{
private:
   // static int id;
    int quantity;
    double price;
    string name;
public:
    Item()
    {
     //   id++;
        quantity=0;
        price=0;
        name=" ";

    }
    Item(int quantityItem,double priceItem,string nameItem)
    {
       // id++;
        quantity=quantityItem;
        price=priceItem;
        name=nameItem;
    }
   Item(Item&ob)
     {
         name=ob.name;
         quantity=ob.quantity;
         price=ob.price;

     }
    void setquantity(int quantitItem)
    {
        quantity=quantitItem;
    }
    int getquantity()
    {
        return quantity;
    }
    void setprice(double priceItem)
    {
        price=priceItem;
    }
    double getprice()
    {
        return price;
    }
    void setname(string nameItem)
    {
        name=nameItem;
    }
    string getname()
    {
        return name;
    }
    bool operator==(Item &ob)
    {
        if(name==ob.name)
            return true;
        else
            return false;
    }
    void operator+=(Item&ob)
    {

        quantity+=ob.quantity;

    }
    void operator-=(Item&ob)
    {

        quantity-=ob.quantity;

    }
    friend istream &operator>>(istream &is,Item&obj);
    friend ostream&operator<<(ostream &os,Item&obj);
    friend class seller;
};
    istream&operator>>(istream&is,Item&obj)
    {
        cout<<"Enter your nameItem :"<<endl;
        is>>obj.name;
        cout<<"Enter quantity : "<<endl;
        is>>obj.quantity;
        cout<<"Enter price : "<<endl;
        is>>obj.price;
        return is;
    }
    ostream&operator<<(ostream&os,Item &obj)
    {
        os<<"name: "<<obj.name<<"   quantity : "<<obj.quantity<<"   price: "<<obj.price<<endl;
        return os;
    }
  //intialize id
  //int Item::id=0;

class seller
{
private:
    string name,email;
    int maxItem;
    Item*arr;
    map<string,double>totalItemprice;
    double totalpricesold=0;
public:
    seller(string nameSeller,string emailSeller,int maxItem)
    {
        name=nameSeller;
        email=emailSeller;
        this->maxItem=maxItem;
        arr=new Item[maxItem];
    }

    bool addItem(Item&obj)
     {
         bool status;
         for(int i=0;i<maxItem;i++)
         {
             if(arr[i]==obj)
             {
                arr[i]+=obj;
                status=true;
                break;
             }
             else if(arr[i].getname()==" ")
             {
                 arr[i]=obj;
                 status=false;
                 break;
             }
             else
             {
                 status=false;
             }
         }
         return status;
     }
 bool sellItem(string nameItem,int quantityItem)
    {
        bool status;
        Item item;
        item.name=nameItem;
        item.quantity=quantityItem;
        bool flag=false;
        for(int i=0;i<maxItem;i++)
        {
            if(arr[i]==item)
            {
                status=true;
                if(item.quantity<=arr[i].quantity)
                {
                    arr[i]-=item;
                    cout<<"The Price : "<<arr[i].getprice()*quantityItem<<endl;
                    cout<<"The quantity of "<<nameItem<<" after sell : "<<arr[i].quantity<<endl;
                    map<string,double>::iterator itr;
                    for(itr=totalItemprice.begin();itr!=totalItemprice.end();itr++)
                    {
                        if(itr->first==nameItem)
                        {
                            totalItemprice.at(itr->first)=itr->second+(quantityItem*arr[i].getprice());
                            totalpricesold+=quantityItem*arr[i].getprice();
                            flag=true;
                            break;
                        }
                    }
                    if(flag==false)
                    {
                        totalItemprice.insert(make_pair(nameItem,quantityItem*arr[i].getprice()));
                        totalpricesold+=quantityItem*arr[i].getprice();
                    }
                }
                else
                {
                    cout<<"Out of stock "<<endl;
                }
                break;
            }
            else if(arr[i].getname()==" ")
            {
                cout<<nameItem<<" is not exist "<<endl;
                status=false;
                break;
            }
        }
    return status;
    }
    void printPrice_of_itemSold()
    {
           map<string,double>::iterator itr;
           for(itr=totalItemprice.begin();itr!=totalItemprice.end();itr++)
                {
                    cout<<"Name Item : "<<itr->first<<" total price sold Of This item : "<<itr->second<<endl;
                }

    }
    double printTotalpriceSold()
    {
        return totalpricesold;
    }
   void printItem()
    {
        for(int i=0;i<maxItem;i++)
        {
            if(arr[i].getname()==" ")
                break;
            else
            {
                cout<<arr[i];
            }
        }
    }
    void addQuantity(string nameItem,int quantity )
    {
         for(int i=0;i<maxItem;i++)
        {
            if(arr[i].getname()==nameItem)
            {
                arr[i].quantity+=quantity;
                cout<<"The quantity of Item : "<<arr[i].getname()<<" after add quantity : "<<arr[i].getquantity()<<endl;
                break;

            }
            else if(arr[i].getname()==" ")
            {
                cout<<"This item is not exist "<<endl;
                break;
            }
        }
    }
    void editPrice(string nameItem,double newprice)
    {
        for(int i=0;i<maxItem;i++)
        {
            if(arr[i].getname()==nameItem)
            {
                cout<<"The old price of "<<arr[i].getname()<<" : "<<arr[i].getprice();
                arr[i].setprice(newprice);
                cout<<" The new price : "<<arr[i].getprice()<<endl;
                break;
            }
            else if(arr[i].getname()==" ")
            {
                cout<<"This item is not exist "<<endl;
                break;
            }
        }
    }
    friend ostream& operator<<(ostream&os,seller &obj);
    ~seller()
    {
        delete[]arr;
    }

};
 ostream&operator<<(ostream&os,seller&obj)
 {
     os<<"name : "<<obj.name<<endl<<"email : "<<obj.email<<endl<<"max item : "<<obj.maxItem<<endl;
     return os;
 }
int main()
{

    string nameSeller,emailSeller;
    int maxitem;
    cout<<"Enter your name : "<<endl;
    getline(cin,nameSeller);
    cout<<"Enter your email : "<<endl;
    getline(cin,emailSeller);
    cout<<"Enter your store capacity : "<<endl;
    cin>>maxitem;
    seller obj(nameSeller,emailSeller,maxitem);
    while(true)
    {

        string nameItem;
        int  count,quantityItem;
        double newPrice;
        cout<<"choose from the menu : "<<endl;
        cout<<"1-Print my info "<<endl;
        cout<<"2-Add an item "<<endl;
        cout<<"3-Sell an Item "<<endl;
        cout<<"4-Print items "<<endl;
        cout<<"5-Add quantity to the Item "<<endl;
        cout<<"6-Edit price of Item "<<endl;
        cout<<"7-Total price of items "<<endl;
        cout<<"8-Total price sold  "<<endl;
        cout<<"9-To EXIT"<<endl;
        cout<<"Enter your choice : "<<endl;
        cin>>count;
        if(count==1)
        {
           cout<<obj;
        }
       else if(count==2)
        {
           Item item;
           cin>>item;
           obj.addItem(item);
        }
        else if(count==3)
        {

            cout<<"Enter your name and quantity"<<endl;
            cin>>nameItem;
            cin>>quantityItem;
            obj.sellItem(nameItem,quantityItem);
        }
        else if(count==4)
        {
            obj.printItem();
        }
        else if(count==5)
        {
             cout<<"Enter your name and quantity"<<endl;
             cin>>nameItem;
             cin>>quantityItem;
             obj.addQuantity(nameItem,quantityItem);
        }
        else if(count==6)
        {

            cout<<"Enter The item you want To edit price : "<<endl;
            cin>>nameItem;
            cout<<"Enter The New Price : "<<endl;
            cin>>newPrice;
            obj.editPrice(nameItem,newPrice);
        }
        else if(count==7)
        {
            obj.printPrice_of_itemSold();
        }
        else if(count==8)
        {
            cout<<"The Total price of items sold "<<obj.printTotalpriceSold()<<endl;
        }
        else if(count==9)
        {
            exit(0);
        }
    }
    return 0;

}
