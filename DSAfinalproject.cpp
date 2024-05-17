#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct customer customer;   // structure for customer details Array
 struct customer{
    long long int accNo,cardNo,phoneNo;
    int pin,balance;
    customer *link2;
}*new2,*head2=NULL,*last2=NULL,*temp2;

typedef struct transaction transaction;   // structure for transactions SLL
 struct transaction{
    long long int senderAcc,receiverAcc;
    int transAmount;
    transaction *link;
}*new,*head=NULL,*last=NULL,*temp;

void create(long long int inputAccNo,long long int receiverAccNo,int inputAmount)   // create functioin for transactions SLL
{   
    new= (transaction *)malloc(sizeof(transaction));
    new->link= NULL;
    //new->transId=printId;
    new->senderAcc=inputAccNo;
    new->receiverAcc=receiverAccNo;
    new->transAmount=inputAmount;
}
void create2(long long int accNo,long long int cardNo,long long int phoneNo,int pin,int balance)   // create functioin for customer SLL
{   
    new2= (customer *)malloc(sizeof(customer));
    new2->link2= NULL;
    //new->transId=printId;
    new2->accNo=accNo;
    new2->cardNo=cardNo;
    new2->phoneNo=phoneNo;
    new2->pin=pin;
    new2->balance=balance;
}
void insert2(long long int accNo,long long int cardNo,long long int phoneNo,int pin,int balance) 
{
    create2(accNo,cardNo,phoneNo,pin,balance);
    if(head2==NULL)
    {
        head2=new2;
        last2=new2;
    }
    else
    {
        last2->link2=new2;
        last2=new2;
    }
}
void delete2(long long int accNo,int pin){
    temp2=head2;
    while(temp2!=NULL){
        if(temp2->accNo==accNo && temp2->pin==pin){
            printf("The customer with accNo%lld is delted",temp2->accNo);
            free(temp2);
        }
     temp2=temp2->link2;
    }
}

 // insert function for transactions occured
void insert(long long int inputAccNo,long long int receiverAccNo,int inputAmount) 
{
    create(inputAccNo,receiverAccNo,inputAmount);
    if(head==NULL)
    {
        head=new;
        last=new;
    }
    else
    {
        last->link=new;
        last=new;
    }
}

void display(long long int account)  // display function for printing transactions
{   
    int flag=0;
    if(head==NULL)
        printf("\nYour Account has no transaction records!!!\n");
    else{
        temp=head;
        printf("\nTransacions Occured : \n");
        while(temp!=NULL)
        {   
            if(temp->senderAcc==account || temp->receiverAcc==account)
            {
                printf("%lld %lld %d\n",temp->senderAcc,temp->receiverAcc,temp->transAmount);
                flag=1;
            }
            temp=temp->link;
        }
        if(flag==0)
                printf("\nYour account has no transaction records!!!\n");
    }
}

int pinChange(long long int inputCardNo);

void main()
{   
    long long int accNo,cardNo,phoneNo;
    int pin,balance;
    
    
    int choice,choice2,ch,i,flag=0,flag2=0;
    int inputPin,newPin;
    int inputAmount,inputBalance;
    long long int inputCardNo,inputAccNo,receiverAccNo; 
    int withdrawAmount,creditamount;
    
    
    printf("\t---------------------------------------------------------------------------------------------\n");
    printf("\n\t\tWELCOME TO DIGITAL ATM\n");
    while(1){
        labelnew:
        printf("\n");
        printf("\t1.Insert customer \n");
        printf("\t2.Delete customer \n");
        printf("\t3.Proceed To ATM \n");
        printf("(Insert first if no customers added) \n");
        printf("\nEnter choice: ");
        scanf("%d",&choice2);
        switch(choice2)
        {
            case 1: printf("\nAcc Number: ");
                scanf("%lld",&accNo);
                printf("Card Number: ");
                scanf("%lld",&cardNo);
                printf("Phone Number: ");
                scanf("%lld",&phoneNo);
                printf("PIN: ");
                scanf("%d",&pin);
                printf("Balance: ");
                scanf("%d",&balance);
                insert2(accNo,cardNo,phoneNo,pin,balance);
                break;
            case 2: printf("\nAcc Number: ");
                scanf("%lld",&accNo);
                printf("PIN: ");
                scanf("%d",&pin);
                delete2(accNo,pin);
                break;
            case 3:goto labelAuth;
            default:printf("\n\t\tINVALID INPUT\n");
        }
    }
    labelAuth: printf("\n\tLogin Page ");
    printf("\nEnter your Atm Card Number : ");
    scanf("%lld",&inputCardNo);
    printf("Enter your PIN : ");
    scanf("%d",&inputPin);
    flag=0;
    temp2=head2;
    while(temp2!=NULL){
        if(inputCardNo==temp2->cardNo && inputPin==temp2->pin)
        {   
            flag=1;
            inputAccNo=temp2->accNo;
            inputBalance=temp2->balance;
        }
        temp2=temp2->link2;
    }
    if(flag==0)
    {
        printf("\nInvalid credentials!\nPlease try again...\n\n");
        goto labelAuth;
    }
    else
    {
        labelChoice: printf("\n1. Withdraw\n");
        printf("2. Transfer Money\n");
        printf("3. PIN Change\n");
        printf("4. Transaction History\n");
        printf("5. Balance Enquiry\n");
        printf("6. Credit money\n");
        printf("7. Add or Delete customer\n");
        printf("8. Back to Login Page\n");
        printf("9. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        temp2=head2;
        while(temp2!=NULL){
            if(inputCardNo==temp2->cardNo && inputPin==temp2->pin)
            {   
                flag=1;
                inputAccNo=temp2->accNo;
                inputBalance=temp2->balance;
            }
            temp2=temp2->link2;
        }
        switch(choice)
        {
            case 1: labelWithdraw: printf("\nEnter amount to withdraw: ");
                    scanf("%d",&withdrawAmount);
                    if(withdrawAmount<=0)
                    {
                        printf("\nAmount must be greater than 0 \nTry Again!!!\n");
                        goto labelWithdraw;
                        
                    }
                        if(inputBalance<withdrawAmount)
                        {
                            printf("Insufficient balance!!!\n");
                            goto labelChoice;
                        }
                        else
                        {   temp2=head2;
                            while(temp2!=NULL)
                            {
                                if(inputCardNo==temp2->cardNo)
                                {   
                                    temp2->balance-=withdrawAmount;
                                    printf("\nRs.%d has been withdrawal sucessfully...\n",withdrawAmount);
                                    printf("Current balance: %d\n",temp2->balance);
                                    insert(inputAccNo,inputAccNo,withdrawAmount);
                                }
                                temp2=temp2->link2;
                            }
                        }
                    break;
            case 2: labelConfirmAcc: printf("\nEnter receiver's account number: ");
                    scanf("%lld",&receiverAccNo);
                    temp2=head2;
                    while(temp2!=NULL)
                    {   
                        if(receiverAccNo==temp2->accNo)
                            flag2=1;
                        temp2=temp2->link2;    
                    }
                    
                    if(flag2==1)
                    {
                        printf("\nDo you want to transfer money to Account number %lld\n",receiverAccNo);
                        printf("Enter 1 to transfer or 0 to re-enter account number: ");
                        scanf("%d",&ch);
                        if(ch!=1)
                            goto labelConfirmAcc;
                        printf("\nEnter amount to be transferred: ");
                        scanf("%d",&inputAmount);
                        if(inputAmount<=0)
                        {
                            printf("\nAmount must be greater than 0\nTransaction cancelled...\nTry Again!!!\n");
                            goto labelConfirmAcc;
                        }
                        if(inputBalance<inputAmount)
                        {
                            printf("Insufficient Balance...\n");
                            goto labelChoice;
                        }
                        else{
                            temp2=head2;
                            while(temp2!=NULL)
                            {
                                if(inputCardNo==temp2->cardNo)
                                {
                                    temp2->balance-=inputAmount;
                                    printf("Your Account's remaining balance : %d\n",temp2->balance);
                                }
                                temp2=temp2->link2;
                            }
                            temp2=head2;
                            while(temp2!=NULL)
                            {
                                if(receiverAccNo==temp2->accNo)
                                {
                                    temp2->balance+=inputAmount;
                                    //printf("Receiver balance = %d\n",c1[i].balance);
                                    printf("Rs.%d has been transferred sucessfully to Account number %lld\n",inputAmount,receiverAccNo);
                                }
                                temp2=temp2->link2;
                            }
                        }
                        insert(inputAccNo,receiverAccNo,inputAmount);
                    }
                    else
                    {
                        printf("This Account do not exits...\nTry Again!");
                        goto labelConfirmAcc;
                    }
                    break;
            case 3: newPin=pinChange(inputCardNo);
                    if(newPin<0)
                    {
                        printf("\nInvalid input\nPin must be positive\n");
                        break;
                    }
                    temp2=head2;
                    while(temp2!=NULL)
                    {
                        if(inputCardNo==temp2->cardNo)
                        {   
                            printf("\nPIN changed sucessfully...\n");
                            printf("Previous Pin is %d\n",temp2->pin);
                            temp2->pin=newPin;
                            printf("New PIN : %d\n",temp2->pin);
                        }
                        temp2=temp2->link2;
                    }
                    break;
            case 4: display(inputAccNo);
                    break;
            case 5: temp2=head2;
                    while(temp2!=NULL)
                    {
                        if(inputCardNo==temp2->cardNo)
                            printf("\nYour Account balance is Rs.%d\n",temp2->balance);
                        temp2=temp2->link2;
                    }
                    break;
            case 6: labelCredit: printf("\nEnter amount to credit: ");
                    scanf("%d",&creditamount);
                    if(creditamount<=0)
                    {
                        printf("\nAmount must be greater than 0 \nTry Again!!!\n");
                        goto labelCredit;
                        
                    }
                    else
                        {   temp2=head2;
                            while(temp2!=NULL) 
                            {
                                if(inputCardNo==temp2->cardNo)
                                {   
                                    temp2->balance+=creditamount;
                                    printf("\nRs.%d has been credited sucessfully...\n",creditamount);
                                    printf("Remaining balance: %d\n",temp2->balance);
                                    insert(inputAccNo,inputAccNo,creditamount);
                                }
                                temp2=temp2->link2;
                            }
                        }
                    break;
            case 7: goto labelnew;
                    break;
            case 8: goto labelAuth;        
            case 9: exit(0);
                    break;
            default: printf("\nInvalid choice...\nPlease enter a valid choice between 1 to 8\n");
        }
        goto labelChoice;
    }
}

int pinChange(long long int inputCardNo)
{   int newPin,confirmPin,changedPin;
    labelPinChange: printf("\nEnter New PIN (4-digit only): ");
    scanf("%d",&newPin);
    printf("Confirm New PIN : ");
    scanf("%d",&confirmPin);
    if(newPin==confirmPin)
        changedPin=newPin;
    else
    {   
        printf("\nPin did not match...\nTry Again!\n");
        goto labelPinChange;
    }
    return changedPin;
}