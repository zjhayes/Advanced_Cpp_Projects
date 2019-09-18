// Food Truck Cash Register that keeps track of inventory.

// Zachary Hayes - zjhayes@dmacc.edu - August 27th, 2019

// The features I added save and load the inventory data so the user doesn't have to  re-enter it every day.
// The first time you run the program, you'll have to initialize the inventory. It will save, and then after
// you take purchases it will save again.
// Then, when you run the program again, it will recognize the save file and load in the inventory data.
// If any part of the inventory is below the "low inventory threshold", the user will be given the option
// to "restock" (or reinitialize).

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

/////// INGREDIENT CLASS ///////

class Ingredient
{
private:
    string name;
    int currentInventory;
    int maxInventory;
    
public:
    Ingredient(string _name, int _maxInventory)
    {
        name = _name;
        currentInventory = 0; // This will be set by the user.
        maxInventory = _maxInventory;
    }
    
    // Getters and Setters
    string getName()
    {
        return name;
    }
    
    int getMaxInventory()
    {
        return maxInventory;
    }
    
    int getCurrentInventory()
    {
        return currentInventory;
    }
    void setCurrentInventory(int _currentInventory)
    {
        currentInventory = _currentInventory;
    }
    void subtractFromInventory(int _amount)
    {
        currentInventory -= _amount;
    }
    
};

/////// PRODUCT CLASS ///////

class Product
{
protected:
    bool addChilli;                     // True if chilli can be added to product.
    string name;
    float price;
    vector<Ingredient> ingredients;
    vector<int> ingredientAmount;
public:
    Product(string _name, float _price, bool _addChilli)
    {
        name = _name;
        price = _price;
        addChilli = _addChilli;
    }
    
    Product(){}
    
    bool getAddChilli()
    {
        return addChilli;
    }
    
    // Add ingredient to list of ingredients in product.
    void addIngredient(Ingredient _ingredient, int _amount)
    {
        ingredients.push_back(_ingredient);
        ingredientAmount.push_back(_amount);
    }
    
    // Getters and Setters
    string getName()
    {
        return name;
    }
    float getPrice()
    {
        return price;
    }
    int getIngredientIndex(string _name)
    {
        int currentIndex = 0;
        for(auto &ingredient : ingredients)
        {
            if(ingredient.getName() == _name)
            {
                break; // Found correct index.
            }
        }
        return currentIndex;
    }
    vector<Ingredient> getIngredients()
    {
        return ingredients;
    }
    int getIngredientAmount(int index)
    {
        return ingredientAmount[index];
    }
    vector<int> getIngredientAmounts()
    {
        return ingredientAmount;
    }

};

/////// FOOD TRUCK CLASS ///////

class FoodTruck
{
private:
    
    // Set up singleton.
    static FoodTruck* instance;
    FoodTruck(){}
    
    float currency;
    vector<Ingredient*> inventory;
    vector<Product> products;
    float addChilliPrice = 2.00;
    int addChilliAmount = 4; // oz
    
    // Create ingredient objects and add them to inventory.
    void intializeIngredientInventory()
    {
        intializeInventoryItem("hamburger patty", 200); // 0
        intializeInventoryItem("hotdog", 200);          // 1
        intializeInventoryItem("hamburger bun", 75);    // 2
        intializeInventoryItem("hotdog bun", 75);       // 3
        intializeInventoryItem("chilli", 500);          // 4
        intializeInventoryItem("fry basket", 75);       // 5
        intializeInventoryItem("soda", 200);            // 6
    }
    
    void intializeInventoryItem(string _name, int _maxAmount)
    {
        Ingredient* newIngredient = new Ingredient(_name, _maxAmount);
        inventory.push_back(newIngredient);
    }
    
    // A method that isn't going to scale well and should be refactored.
    void initializeProducts()
    {
        int burgerAmounts[] = {1,0,1,0,0,0,0}; // These are like punchcards.
        initializeAProduct("Hamburger", 5.00, true, burgerAmounts);
        int hotdogAmounts[] = {0,1,0,1,0,0,0};
        initializeAProduct("Hotdog", 5.00, true, hotdogAmounts);
        int chilliAmounts[] = {0,0,0,0,12,0,0};
        initializeAProduct("Chilli", 4.00, false, chilliAmounts);
        int friesAmount[] = {0,0,0,0,0,1,0};
        initializeAProduct("Fries (basket)", 7.00, true, friesAmount);
        int sodaAmount[] = {0,0,0,0,0,0,1};
        initializeAProduct("Soda", 2.00, false, sodaAmount);
    }
    
    // Create a product and add to product list.
    void initializeAProduct(string _name, float _price, bool _addChilli, int ingredientAmounts[])
    {
        Product newProduct = Product(_name, _price, _addChilli);
        
        int ingredientIndex = 0;
        for(auto ingredient : getInventory()) // Add ingredients to product.
        {
            int ingredientAmount = ingredientAmounts[ingredientIndex];
            if(ingredientAmount > 0)
            {
                newProduct.addIngredient(*ingredient, ingredientAmount);
            }
            ingredientIndex++;
        }
        products.push_back(newProduct);
    }
    
    // Get inventory input from user and validate.
    int takeInventoryInput(Ingredient* _ingredient)
    {
        int inventoryInput;
        int maxInventory = _ingredient->getMaxInventory();
        
        cout << _ingredient->getName() << " (" << _ingredient->getMaxInventory() << "): ";
        cin >> inventoryInput;
        
        if(inventoryInput < 0 or inventoryInput > maxInventory)
        {
            cout << "Invalid input. The max inventory for this item is " << maxInventory << endl;
            cout << "Try again. ";
            inventoryInput = takeInventoryInput(_ingredient);
        }
        return inventoryInput;
    }
    
public:
    
    // Get singleton instance.
    static FoodTruck* getInstance()
    {
        if(instance == 0)
        {
            instance = new FoodTruck();
            instance->intializeIngredientInventory();
            instance->initializeProducts();
        }
        
        return instance;
    }
    
    vector<Ingredient*> getInventory()
    {
        return inventory;
    }
    
    vector<Product> getProducts()
    {
        return products;
    }
    
    float getCurrency()
    {
        return currency;
    }
    
    float getAddChilliPrice()
    {
        return addChilliPrice;
    }
    
    int getAddChilliAmount()
    {
        return addChilliAmount;
    }
    
    int getIngredientIndex(string _name)
    {
        int currentIndex = 0;
        for(auto &ingredient : inventory)
        {
            if(ingredient->getName() == _name)
            {
                break; // Found correct index.
            }
            currentIndex++;
        }
        return currentIndex;
    }

    // Set initial inventory from user input.
    void initializeInventoryFromConsole()
    {
        cout << "Initialize Inventory" << endl;
        
        for(auto &ingredient : getInventory())
        {
            int currentInventory = takeInventoryInput(ingredient);
            ingredient->setCurrentInventory(currentInventory);
        }
    }
    
    // Use ingredients and create product.
    void makeProduct(Product* _product)
    {
        for(auto ingredient : _product->getIngredients())
        {
            // Subtract from ingredients in stock.
            int inventoryIndex = getIngredientIndex(ingredient.getName());
            string ingredientName = ingredient.getName();
            int ingredientIndex = _product->getIngredientIndex(ingredientName);
            int ingredientAmount = _product->getIngredientAmount(ingredientIndex);
            inventory[inventoryIndex]->subtractFromInventory(ingredientAmount);
        }
    }
    
    // Checks list of ingredients against ingredients in stock.
    bool checkIngredients(Product* _product)
    {
        bool passed = true;
        for(auto &ingredient : _product->getIngredients())
        {
            int inventoryIndex = getIngredientIndex(ingredient.getName());
            int currentInventory = inventory[inventoryIndex]->getCurrentInventory();
            string ingredientName = ingredient.getName();
            int ingredientIndex = _product->getIngredientIndex(ingredientName);
            int ingredientAmount = _product->getIngredientAmount(ingredientIndex);
            if(ingredientAmount >= currentInventory)
            {
                cout << "Not enough " << ingredient.getName() << " in inventory." << endl;
                passed = false;
            }
        }
        
        return passed;
    }
    
    // Add money to total currency.
    void deposit(float _amount)
    {
        currency += _amount;
    }
    
};

/////// PRODUCT ADD CHILL CLASS ///////

class ProductAddChilli : public Product
{
public:
    
    int chilliIndex = FoodTruck::getInstance()->getIngredientIndex("chilli");
    Ingredient chilli = *FoodTruck::getInstance()->getInventory()[chilliIndex];
    int chilliAmount = FoodTruck::getInstance()->getAddChilliAmount();
    
    ProductAddChilli()
    {
        Product();
    }
    
    ProductAddChilli(Product _product)
    {
        Product();
        name = _product.getName() + " (add chilli)";
        price = _product.getPrice()+ FoodTruck::getInstance()->getAddChilliPrice();
        ingredients = _product.getIngredients();
        ingredients.push_back(chilli);
        ingredientAmount = _product.getIngredientAmounts();
        ingredientAmount.push_back(chilliAmount);
    }
};


/////// MAIN CLASS ///////


// Constants
const int SENTINEL = 0;
const float SALES_TAX = .05;
const float LOW_INVENTORY_PERCENT = .2;

// Function Declarations
void initializeInventory();
void openRegister();
void closeRegister();
void printMenu();
void takeCustomerOrders();
bool validateOrder(int);
void askToAddChilli(Product);
void processOrder(Product*);
void processOrder(ProductAddChilli*);
float calculatePriceWithTax(float);
bool checkInventoryAlerts();
void saveInventory();
bool loadInventory();
bool askToRestock();

// Weird C++ stuff.
FoodTruck* FoodTruck::instance = 0;

int main()
{
    cout << "Rebel Food Truck" << endl << endl;
    initializeInventory();
    openRegister();
    closeRegister();
    
    return 0;
}

// Attempt to load inventory, otherwise take inventory via user input.
void initializeInventory()
{
    bool loaded = loadInventory();
    
    if(loaded && checkInventoryAlerts()) // If inventory is low, asks to restock.
    {
        loaded = !askToRestock();
    }
    
    if(!loaded)
    {
        FoodTruck::getInstance()->initializeInventoryFromConsole();
    }
    saveInventory();
}

bool askToRestock()
{
    string answer;
    cout << "Inventory is low. Restock inventory? (y/n): ";
    cin >> answer;
    
    char answerLowerChar = tolower(answer.front(), locale());
    
    if(answerLowerChar == 'y')
    {
        return true;
    }
    else if(answerLowerChar == 'n')
    {
        return false;
    }
    else
    {
        cout << "Invalid entry. Try again." << endl;
        return askToRestock();
    }
}

// Take and process customer orders.
void openRegister()
{
    cout << endl << "Open for business." << endl;
    printMenu();
    takeCustomerOrders();
}

// Print list of products and prices.
void printMenu()
{
    cout << endl << "------------------------------" << endl;
    cout << "            MENU" << endl;
    cout << "------------------------------" << endl << endl;
    
    int menuItem = 1;
    float addChilliPrice = FoodTruck::getInstance()->getAddChilliPrice();
    
    for(auto &product : FoodTruck::getInstance()->getProducts())
    {
        cout << std::fixed << std::setprecision(2);
        string name = product.getName();
        float price = product.getPrice();
        cout << menuItem << ". " << name << setw(20 - (int)name.length()) << "$" << price << endl;
        
        if(product.getAddChilli())
        {
            cout << "     + add chilli" << setw(6) << "$" << (price + addChilliPrice) << endl;
        }
        cout << "- - - - - - - - - - - - - - -" << endl;
        menuItem++;
    }
}

// Take customer orders until exited.
void takeCustomerOrders()
{
    cout << endl << "Place orders using menu number." << endl;
    cout << "Or enter '"<< SENTINEL << "' to close register." << endl << endl;
    
    bool exit = false;
    
    while(!exit)
    {
        int order;
        
        cout << "Order: ";
        cin >> order;
        
        if(!cin)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid entry. Please enter the product's menu number." << endl;
        }
        else
        {
            exit = validateOrder(order);
        }
    }
}

// Validate and process order. Returns true when ready to exit.
bool validateOrder(int _order)
{
    FoodTruck* truck = FoodTruck::getInstance();
    
    if(_order > 0 && _order <= truck->getProducts().size())
    {
        int orderIndex = _order - 1; // Menu number is 1 more than product index.
        Product product = truck->getProducts()[orderIndex];
        if(product.getAddChilli())
        {
            askToAddChilli(product);
        }
        else
        {
            processOrder(&product);
        }
    }
    else if(_order == SENTINEL)
    {
        return true;
    }
    else
    {
        cout << "Invalid menu item. Try again." << endl;
    }
    
    return false;
}

// Processes order and outputs results.
void processOrder(Product* _product)
{
    FoodTruck* truck = FoodTruck::getInstance();
    
    if(truck->checkIngredients(_product)) // Check ingredients against stock
    {
        truck->makeProduct(_product);
        float totalPrice = calculatePriceWithTax((*_product).getPrice());
        cout << "Price: $" << totalPrice << endl << endl;
        truck->deposit(totalPrice); // Add to currency.
    }
}

// Process chilli orders.
void processOrder(ProductAddChilli* _product)
{
    FoodTruck* truck = FoodTruck::getInstance();
    
    if(truck->checkIngredients(_product)) // Check ingredients against stock
    {
        truck->makeProduct(_product);
        float totalPrice = calculatePriceWithTax((*_product).getPrice());
        cout << "Price: $" << totalPrice << endl << endl;
        truck->deposit(totalPrice); // Add to currency.
    }
}

float calculatePriceWithTax(float price)
{
    return price + (price * SALES_TAX);
}

void askToAddChilli(Product _product)
{
    string answer;
    cout << "Add chilli? (y/n): ";
    cin >> answer;
    
    char answerLowerChar = tolower(answer.front(), locale());
    
    if(answerLowerChar == 'y')
    {
        ProductAddChilli chilliProduct = static_cast<ProductAddChilli>(_product);
        processOrder(&chilliProduct);
    }
    else if(answerLowerChar == 'n')
    {
        processOrder(&_product);
    }
    else
    {
        cout << "Invalid entry. Try again." << endl;
        askToAddChilli(_product);
    }
}

// Output sales data.
void closeRegister()
{
    saveInventory();
    checkInventoryAlerts();
    
    cout << endl << "Total earnings: $" << FoodTruck::getInstance()->getCurrency();
    cout << endl << endl;
}

// If item is below 20% in inventory, prints alert.
bool checkInventoryAlerts()
{
    bool alertFound = false;
    FoodTruck* truck = FoodTruck::getInstance();
    vector<Ingredient*> inventory = truck->getInventory();
    
    for(auto &ingredient : inventory)
    {
        if(ingredient->getCurrentInventory() < (ingredient->getMaxInventory() * LOW_INVENTORY_PERCENT))
        {
            cout << ingredient->getName() << " is below 20%" << endl;
            alertFound = true;
        }
    }
    
    return alertFound;
}

// Saves inventory to a text file so it can be reloaded.
void saveInventory()
{
    ofstream writer("food_truck_inventory.txt");
    FoodTruck* truck = FoodTruck::getInstance();
    vector<Ingredient*> inventory = truck->getInventory();
    string inventoryString;
    
    for(auto &ingredient : inventory)
    {
        string itemString = to_string(ingredient->getCurrentInventory());
        inventoryString.append(itemString + "\n");
    }
    
    if(writer)
    {
        writer << inventoryString;
    }
    else
    {
        cout << "Error: Could not update inventory file." << endl;
    }
    
    writer.close();
}

// Load inventory, returns true is successful.
bool loadInventory()
{
    FoodTruck* truck = FoodTruck::getInstance();
    vector<Ingredient*> inventory = truck->getInventory();
    ifstream reader("food_truck_inventory.txt");
    
    if(reader)
    {
        for(auto ingredient : inventory)
        {
            if(!reader.eof())
            {
                string line;
                getline(reader, line);
                if(line == ""){break;}
                int currentInventory = stoi(line);
                ingredient->setCurrentInventory(currentInventory);
            }
        }
        return true;
    }
    
    return false;
}
