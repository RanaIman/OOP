//MEDICAL STORE MANAGEMENT SYSTEM

/*   GROUP MEMBERS
		1. MUHAMMAD HUZAIFA (065) 03-134222-065
		2. MUHAMMAD HASSAN KHAN (064) 03-134222-064
		3. MUHAMMAD IMAN KHAN (068) 03-134222-068
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <exception>
#include <conio.h>
#include <regex>
#include <chrono>
#include <stdio.h>

using namespace std;

const int MAX_SIZE = 1000;

class MedicalItem
{
    protected:
        string name;
        float price;
        string manufacturer;
        string manufacturerDate;
        string expiryDate;
        int quantity;
        float wholesalePrice;
        float retailPrice;
        double discount;
    public:
        MedicalItem(const string& name, float wholesalePrice, const string& manufacturer, string manufacturerDate, string expiryDate, int quantity) : name(name), manufacturer(manufacturer), manufacturerDate(manufacturerDate), expiryDate(expiryDate), quantity(quantity), wholesalePrice(wholesalePrice)
        {
            // Calculate the retail price with a 40% markup from the wholesale price
            retailPrice = wholesalePrice + (0.4 * wholesalePrice);
            price = retailPrice + (0.15 * retailPrice);
            // Apply a 5% discount to the price
            discount = price * (5.0/100);
        }

        const string& getName()
        {
        return name;
        }
        
        void setName(string n)
        {
        	name = n;
        }
		
		double getDiscount()
		{
			return discount;
		}
		
        float getPrice()
        {
            return price;
        }

        const string& getManufacturer()
        {
            return manufacturer;
        }

        string getManufacturerDate()
        {
            return manufacturerDate;
        }

        string getExpiryDate()
        {
            return expiryDate;
        }

        int getQuantity()
        {
            return quantity;
        }

        float getWholesalePrice()
        {
            return wholesalePrice;
        }

        float getRetailPrice()
        {
            return retailPrice;
        }

        void setQuantity(int newQuantity)
        {
            quantity = newQuantity;
        }

        void display()
        {
            cout << "\n\n\tName : " << name << endl;
            cout << "\tPrice : " << price << endl;
            cout << "\tManufacturer : " << manufacturer << endl;
            cout << "\tManufacturer Date : " << manufacturerDate << endl;
            cout << "\tExpiry Date : " << expiryDate << endl;
            cout << "\tQuantity : " << quantity << endl;
            cout << "\tWholesale Price : " << wholesalePrice << endl;
            cout << "\tRetail Price : " << retailPrice << endl;
            cout << endl;
        }
};

class Bill
{
    private:
        string customerName;
        time_t purchaseDate;
        MedicalItem* item;
        int quantity;

    public:
        Bill(const string& customerName, time_t purchaseDate, MedicalItem* item, int quantity) : customerName(customerName), purchaseDate(purchaseDate), item(item), quantity(quantity) {}

        void generateBill()
        {
        	system("cls");
            cout << "\n\n\t------------ Bill ------------" << endl;
            cout << "\n\tCustomer Name : " << customerName << endl;
            cout << "\tPurchase Date : " << ctime(&purchaseDate);
            cout << "\tMedicine : " << item->getName() << endl;
            cout << "\tQuantity : " << quantity << endl;
            float totalAmount = item->getRetailPrice() * quantity;
            cout << "\tTotal Amount : " << totalAmount << endl;
            float discount = item->getDiscount();
            if (discount > 0)
            {
            float discountAmount = totalAmount * (discount / 100);
            cout << "\tDiscount : " << discountAmount << endl;
            cout << "\tFinal Amount : " << totalAmount - discountAmount << endl;
            }
            cout << "\n\tThank You For Coming. Please Come Again." << endl;
            cout << "\n\t-------------------------------" << endl;
        }
};

class MedicalStore
{
    private:
        MedicalItem* inventory[MAX_SIZE];
        int itemCount;

    public:
    	// Constructor
        MedicalStore() : itemCount(0) {}
        
        // Destructor
        ~MedicalStore()
	    {
	        for (int i = 0; i < itemCount; i++)
	        {
	            delete inventory[i];
	        }
	    }
        
        // A Function To Save The Inventory From The File
        void saveInventoryToFile()
	    {
	        ofstream file("inventory.txt", ios::app | ios::out);
	
	        if (file.is_open())
	        {
	            for (int i = 0; i < itemCount; i++)
	            {
	                //inventory[i]->writeToFile(file);
	                file << inventory[i]->getName() << "," << inventory[i]->getWholesalePrice() << "," << inventory[i]->getManufacturer() << "," << inventory[i]->getManufacturerDate() << "," << inventory[i]->getExpiryDate() << "," << inventory[i]->getQuantity() << "\n";
	            }
	
	            file.close();
	            cout << "\n\n\tInventory Saved To File : " << "inventory.txt" << endl;
	        }
	        else
	        {
	            cout << "\n\n\tFailed To Open File : " << "inventory.txt" << endl;
	        }
	    }
	
	    // A Function To load The Inventory From The File
	    void loadInventoryFromFile()
	    {
	        ifstream file("inventory.txt", ios::in | ios::out);
	
	        if (file.is_open())
	        {
	            string line;
	
	            while (getline(file, line))
				{
				    // Read The Item's Data From The File
				    string name;
				    float wholesalePrice;
				    string manufacturer;
				    string manufacturerDate;
				    string expiryDate;
				    int quantity;
				
				    // Parse the line and assign values to variables
				
				    // Create a New MedicalItem Object And Add It To The Inventory
				    MedicalItem* item = new MedicalItem(name, wholesalePrice, manufacturer, manufacturerDate, expiryDate, quantity);
				    inventory[itemCount++] = item;
				    itemCount++;
				}

	
	            file.close();
	            cout << "\n\n\tInventory Loaded From File : inventory.txt" << endl;
	        }
	        else
	        {
	            cout << "\n\n\tFailed To Open File : inventory.txt" << endl;
	        }
	    }
	    
		//Add New Medicine
        void addMedicalItem(const MedicalItem& item)
        {
        	try
			{
		    	if (itemCount >= MAX_SIZE)
        		{
            		throw itemCount;
        		}
    		}
    		catch(...)
    		{
    			cout << "\n\n\tInventory Is Full. Cannot Add More Items." << endl ;
			}
        	inventory[itemCount++] = new MedicalItem(item);
        }

		// Display Medical Items
        void displayMedicalItems()
        {
        	if (itemCount == 0)
        	{
        	    cout << "\n\n\tInventory Is Empty." << endl;
        	}
        	else
        	{
        	    for (int i = 0; i < itemCount; i++)
        	    {
        	        inventory[i]->display();
            	}
        	}
        }

        MedicalItem* findMedicalItem(const string& name)
        {
            for (int i = 0; i < itemCount; i++)
            {
            	if (inventory[i]->getName() == name)
            	{
                	return inventory[i];
            	}
            }
            return nullptr;
        }

        void updateMedicalItemName(const string& currentName, const string& newName)
        {
            MedicalItem* item = findMedicalItem(currentName);
            try
            {
				if (item == nullptr)
            	{
            	    throw item;
            	}
        	}
        	catch(...)
        	{
        		cout << "\n\n\tItem Not Found In Inventory." << endl;
			}
            item->setName(newName);
        }

        void removeMedicalItem(const string& name)
        {
            int index = -1;
            for (int i = 0; i < itemCount; i++)
            {
            	if (inventory[i]->getName() == name)
            	{
                	index = i;
                	break;
            	}
        	}
        	if (index != -1)
        	{
            	delete inventory[index];
            	for (int i = index; i < itemCount - 1; i++)
            	{
                	inventory[i] = inventory[i + 1];
            	}
            	itemCount--;
            	cout << "\n\n\tItem Removed From Inventory." << endl;
        	}
        	else
        	{
        	    cout << "\n\n\tItem Not Found In Inventory." << endl;
        	}
        }
        
        // Restock Your Medicine From The Supplier
        void restockFromSupplier(const string& itemName, int quantityToAdd)
		{
		    int itemIndex = -1;
		    for (int i = 0; i < itemCount; i++)
		    {
		        if (inventory[i]->getName() == itemName)
		        {
		            itemIndex = i;
		            break;
		        }
		    }
		
		    if (itemIndex != -1)
		    {
		        // Item found, update the quantity
		        inventory[itemIndex]->setQuantity ( inventory[itemIndex]->getQuantity() + quantityToAdd );
		        cout << "\n\tRestocked " << itemName << " : " << quantityToAdd << " Units Added." << endl;
		    }
		    else
		    {
		        // If Item Not Found, Add It To The Inventory
		        if (itemCount < MAX_SIZE)
		        {
		        	float wholesalePrice;
		        	string manufacturer, manufacturerDate, expiryDate;
		        	cout << "\tWholesale Price : ";
	                cin >> wholesalePrice;
	                while(wholesalePrice <= 0.0)
	                {
	                	cout << "\n\tPlease Enter A Postive Decimal Number." << endl;
	                	cout << "\tWholesale Price : ";
	                	cin >> wholesalePrice;
					}
	                cout << "\tManufacturer : ";
	                cin.ignore();
	                getline(cin, manufacturer);
	                
	                do
					{
				        cout << "\tManufacturer Date (YYYY-MM-DD): ";
				        getline(cin, manufacturerDate);
				    } while (!isValidDateFormat(manufacturerDate));
	                
	                do
					{
				        cout << "\tManufacturer Date (YYYY-MM-DD): ";
				        getline(cin, manufacturerDate);
				    } while (!isValidDate(manufacturerDate));
					
					do
					{
				        cout << "\tExpiry Date (YYYY-MM-DD): ";
				        getline(cin, expiryDate);
				    } while (!isValidDateFormat(expiryDate));
					
				    do
					{
				        cout << "\tExpiry Date (YYYY-MM-DD): ";
				        getline(cin, expiryDate);
				    } while (!isValidDate(expiryDate));
	                
		            MedicalItem* newItem = new MedicalItem(itemName, wholesalePrice, manufacturer, manufacturerDate, expiryDate, quantityToAdd);
		            inventory[itemCount++] = newItem;
		            cout << "\n\tAdded " << itemName << " To The Inventory : " << quantityToAdd << " Units Added." << endl;
		        }
		        else
		        {
		            cout << "\n\tInventory Is Full. Cannot Add More Items." << endl;
		        }
		    }
		}
		
		// Hide Password
		string getHiddenPassword()
		{
	        string password = "";
	        char ch;
	        while ((ch = _getch()) != '\r') // Reads Characters Until Enter Key Is Pressed
	        {   
				if (ch == '\b') // Handle Backspace
	            {
	 
					{
	                    password.pop_back();
	                    cout << "\b \b"; // Move Cursor Back, Erase Character, Move Cursor Back Again
	                }
	            }
	            else
				{
	                password.push_back(ch);
	                cout << '*'; // Print Asterisk Instead Of The Actual Character
	            }
	        }
	        cout << endl;
	        return password;
	    }
	    
		bool isValidDateFormat(const string& date)
		{
		    regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
		    return regex_match(date, dateRegex);
		}
		
		bool isValidDate(const string& date)
		{
	    		if (!isValidDateFormat(date))
			        return false;
			
			    int year, month, day;
			    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
			
			    struct tm tm = {};
			    tm.tm_year = year - 1900;
			    tm.tm_mon = month - 1;
			    tm.tm_mday = day;
			
			    time_t time = mktime(&tm);
			    return time != -1;
		}
};

class Menu
{
    public:
        virtual void displayMenu() {};
        virtual void handleChoice(int choice, MedicalStore& store) {};
        virtual int getExitChoice() {};
};

class AdminMenu : public Menu
{
    public:
        void displayMenu() override
        {
            cout << "\n\n\t------- Admin Menu -------" << endl;
            cout << "\n\t1. Add Medical Item" << endl;
            cout << "\t2. Display Medical Items" << endl;
            cout << "\t3. Update Medical Item Name" << endl;
            cout << "\t4. Remove Medical Item" << endl;
            cout << "\t5. Restock from Supplier" << endl;
            cout << "\t6. Exit" << endl;
            cout << "\n\tEnter your choice: ";
        }
        
        int getExitChoice() override
        {
        	return 6;
		}

        void handleChoice(int choice, MedicalStore& store) override
        {
            string itemName, currentName, newName;

            switch (choice)
            {
            case 1:
            {
                // Add Medical Item
                // Implement the logic to add a medical item to the store

                string name, manufacturer;
                float wholesalePrice;
                string manufacturerDate, expiryDate;
                int quantity;
				
				system("cls");
                cout << "\n\n\tEnter The Details Of The Medical Item :- " << endl;
                cout << "\n\tName : ";
                cin.ignore();
                getline(cin, name);
                cout << "\tWholesale Price : ";
                cin >> wholesalePrice;
                while(wholesalePrice <= 0.0)
                {
                	cout << "\n\tPlease Enter A Postive & Non-Zero Decimal Number." << endl;
                	cout << "\tWholesale Price : ";
                	cin >> wholesalePrice;
				}
                cout << "\tManufacturer : ";
                cin.ignore();
                getline(cin, manufacturer);
                cout << "\tQuantity : ";
                cin >> quantity;
                
                while( quantity <= 0 )
                {
                	cout << "\n\tPlease Enter Quantity In Terms Of Positive & Non-Zero Number." << endl;
					cout << "\n\tEnter The Quantity To Buy : ";
                	cin >> quantity;
				}
                
                do
				{
					cout << "\n\tManufacturer Date (YYYY-MM-DD) : ";
			        getline(cin, manufacturerDate);
			    } while (!store.isValidDateFormat(manufacturerDate));
                
                do
				{
					cout << "\n\tManufacturer Date (YYYY-MM-DD) : ";
			        getline(cin, manufacturerDate);
			    } while (!store.isValidDate(manufacturerDate));
				
				do
				{
					cout << "\n\tExpiry Date (YYYY-MM-DD) : ";
			        getline(cin, expiryDate);
			    } while (!store.isValidDateFormat(expiryDate));
				
				
			    do
				{
					cout << "\n\tExpiry Date (YYYY-MM-DD) : ";
			        getline(cin, expiryDate);
			    } while (!store.isValidDate(expiryDate));

                try
                {
                    MedicalItem item(name, wholesalePrice, manufacturer, manufacturerDate, expiryDate, quantity);
                    store.addMedicalItem(item);
                    cout << "\n\n\tMedical Item Added Successfully!" << endl;
                }
                catch (const exception& e)
                {
                    cerr << "\n\n\tFailed To Add Medical Item : " << e.what() << endl;
                }
                break;
            }
            case 2:
            {
                // Display Medical Items
                // Implement the logic to display all medical items in the store
				
				system("cls");
                store.displayMedicalItems();
                break;
            }
            case 3:
            {
                // Update Medical Item Name
                // Implement the logic to update the name of a medical item in the store
				
				system("cls");
                cout << "\n\n\tEnter The Current Name Of The Medical Item : ";
                cin.ignore();
                getline(cin, currentName);
                cout << "\n\tEnter The New Name Of The Medical Item : ";
                getline(cin, newName);

                try
                {
                    store.updateMedicalItemName(currentName, newName);
                    cout << "\n\n\tMedical Item Name Updated Successfully!" << endl;
                }
                catch (const exception& e)
                {
                    cerr << "\n\n\tFailed To Update Medical Item Name : " << e.what() << endl;
                }
                break;
            }
            case 4:
            {
                // Remove Medical Item
                // Implement the logic to remove a medical item from the store
                
                system("cls");
                cout << "\n\n\tEnter The Name Of The Medical Item To Remove : ";
                cin.ignore();
                getline(cin, itemName);

                try
                {
                    store.removeMedicalItem(itemName);
                }
                catch (const exception& e)
                {
                    cerr << "\n\n\tFailed To Remove Medical Item : " << e.what() << endl;
                }
                break;
            }
            
            case 5:
            {
                // Restock from Supplier
                // Implement the logic to restock medical items from the supplier
				
				system("cls");
                string itemName;
                int quantity;
                cout << "\n\n\tEnter The Name Of The Medical Item To Restock : ";
                cin.ignore();
                getline(cin, itemName);
                cout << "\n\n\tEnter The Quantity To Restock : ";
                cin >> quantity;
                while( quantity <= 0 )
                {
                	cout << "\n\tPlease Enter Quantity In Terms Of Positive Integers." << endl;
					cout << "\n\tEnter The Quantity To Buy : ";
                	cin >> quantity;
				}

                try
                {
                    store.restockFromSupplier(itemName, quantity);
                    cout << "\n\n\tMedical Item Restocked Successfully!" << endl;
                }
                catch (const exception& e)
                {
                    cerr << "\n\n\tFailed To Restock Medical Item : " << e.what() << endl;
                }
                break;
            }
            
            case 6:
            {
                break;
            }
            default:
            {
                cout << "\n\tInvalid Choice. Please Try Again." << endl;
                break;
            }
            }
        }
};

class CustomerMenu : public Menu
{
    public:
        void displayMenu() override
        {
            cout << "\n\n\t------- Customer Menu -------" << endl;
            cout << "\n\t1. Search Medicine" << endl;
            cout << "\t2. Buy Medicine" << endl;
            cout << "\t3. Exit" << endl;
            cout << "\n\tEnter your choice: ";
        }
        
        int getExitChoice() override
        {
           	return 3;
		}

        void handleChoice(int choice, MedicalStore& store) override
        {

            switch (choice)
            {
            case 1:
            {
                // Search Medicine
                // Implement the logic to search for medicine
				
				system("cls");
                string itemName;
                cout << "\n\n\tEnter The Name Of The Medicine To Search : ";
                cin.ignore();
                getline(cin, itemName);

                MedicalItem* item = store.findMedicalItem(itemName);
                if (item != nullptr)
                {
                    cout << "\n\n\tMedicine Found!" << endl;
                    item->display();
                }
                else
                {
                    cout << "\n\n\tMedicine Not Found." << endl;
                }
                break;
            }
            case 2:
            {
                // Buy Medicine
                // Implement the logic to allow the customer to buy medicine
                system("cls");
                string itemName, customerName;
                int quantity;
                cout << "\n\n\tEnter The Name Of The Medicine To Buy : ";
                cin.ignore();
                getline(cin, itemName);
                cout << "\tEnter The Quantity To Buy : ";
                cin >> quantity;
                while( quantity <= 0 )
                {
                	cout << "\n\tPlease Enter Quantity In Terms Of Positive Integers." << endl;
					cout << "\n\tEnter The Quantity To Buy : ";
                	cin >> quantity;
				}
			
                cout << "\n\tEnter The Name Of The Customer : ";
                cin.ignore();
                getline(cin, customerName);

                MedicalItem* item = store.findMedicalItem(itemName);
                if (item != nullptr)
                {
                    if (item->getQuantity() >= quantity)
                    {
                        item->setQuantity(item->getQuantity() - quantity);

                        time_t purchaseDate = time(nullptr);
                        Bill bill(customerName, purchaseDate, item, quantity);
                        bill.generateBill();
                    }
                    else
                    {
                        cout << "\n\n\tInsufficient Quantity Available." << endl;
                    }
                }
                else
                {
                    cout << "\n\n\tMedicine Not Found." << endl;
                }
                break;
            }
            case 3:
            {
            	
                break;
            }
            default:
            {
                cout << "\n\n\tInvalid Choice. Please Try Again." << endl;
            }
            }
        }
};

class MedicalStoreRunner
{
    private:
        MedicalStore store;
        Menu* currentMenu = new Menu();

    public:
        MedicalStoreRunner() : currentMenu(nullptr) {}

        void run()
        {
            try
            {
                int choice;
                bool exit = false;

                while (!exit)
                {
                    cout << "\n\n\t------- Medical Store Management System -------" << endl;
                    cout << "\n\t1. Admin Login" << endl;
                    cout << "\t2. Customer" << endl;
                    cout << "\t3. Exit" << endl;
                    cout << "\n\tEnter Your Choice : ";
                    cin >> choice;
                    while(choice < 1 || choice >3)
                    {
                    	cout << "\n\tPlease Enter Values From 1 To 3." <<endl;
                    	cout << "\n\tEnter Your Choice : ";
                    	cin >> choice;
					}

                    switch (choice)
                    {
                    case 1:
                    {
                        if (adminLogin())
                        {
                            currentMenu = new AdminMenu();
                            system("cls");
                            runMenu();
                        }
                        break;
                    }
                    case 2:
                    {
                        currentMenu = new CustomerMenu();
                        system("cls");
						runMenu();
                        break;
                    }
                    case 3:
                    {
                        exit = true;
                        break;
                    }
                    default:
                    {
                        cout << "\n\n\tInvalid Choice. Please Try Again." << endl;
                        break;
                    }
                    }
                }
            }
            catch (const exception& e)
            {
                cerr << "\n\tException : " << e.what() << endl;
            }
        }

    private:
        void runMenu()
        {
        int choice;

        while (true)
        {
            currentMenu->displayMenu();
            cin >> choice;

            if (choice == currentMenu->getExitChoice())
            {
                delete currentMenu;
                currentMenu = nullptr;
                break;
            }

            currentMenu->handleChoice(choice, store);
        }
        }

        bool adminLogin()
        {
        	system("cls");
            string username, password;
            cout << "\n\n\tAdmin Login" << endl;
            cout << "\n\tUsername : ";
            cin >> username;
            cout << "\tPassword : ";
            password = store.getHiddenPassword();

            ifstream file("admin.txt");
            string fileUsername, filePassword;
            file >> fileUsername >> filePassword;

            if (username == fileUsername && password == filePassword)
            {
                cout << "\n\n\tLogin Successful!" << endl;
                return true;
            }
            else
            {
                cout << "\n\n\tLogin Failed!" << endl;
                return false;
            }
        }
};

int main()
{
	MedicalStore MS;
	
	// Load inventory from file
	MS.loadInventoryFromFile();
	
    MedicalStoreRunner runner;
    runner.run();
	
	cout << "\n\n\tTHANK YOU" << endl;
	
	// Save inventory to file
	MS.saveInventoryToFile();
	
	//Destructor
	//MS.~MedicalStore();
    return 0;
}