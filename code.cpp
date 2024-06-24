#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define FN "taxing.txt"
 struct Taxing {
    char name[50];
    float income;
    float tax;
} ;
void adding() {
    Taxing nr;
    FILE *fp;
    fp = fopen(FN, "a");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", nr.name);
    printf("Enter income: ");
    scanf("%f", &nr.income);
    if (nr.income <= 250000) {
        nr.tax = 0;
    } else if (nr.income <= 500000 && nr.income > 250000 ) {
        nr.tax = (nr.income *0.05);
    } else if (nr.income <= 750000 && nr.income > 500000) {
        nr.tax = (nr.income *0.01);
	} else if (nr.income <= 1000000 && nr.income > 750000) {
        nr.tax = (nr.income *0.15);
	} else if (nr.income <= 1250000 && nr.income > 1000000) {
        nr.tax = (nr.income *0.2);
	} else if (nr.income <= 1500000 && nr.income > 1250000) {
        nr.tax = (nr.income *0.25);				    
    } else {
        nr.tax = (nr.income *0.3);
    }
    fwrite(&nr, sizeof(Taxing), 1, fp);
    
    printf("Record added successfully.\n");
    fclose(fp);
}
void listing() {
    Taxing rec;
    FILE *fp;
    fp = fopen(FN, "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    printf("%s  %s    %s\n", "Name", "Income", "Tax");
    while (fread(&rec, sizeof(Taxing), 1, fp) == 1) {
        printf("%s %.2f %.2f", rec.name, rec.income, rec.tax);
        printf("\n");
    }
    fclose(fp);
}
void searching(){
	char sea_r[50];
    Taxing rec;
    FILE *fp;
    printf ("Enter name to search: ");
    scanf("%s", sea_r);
    fp = fopen(FN, "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    while (fread(&rec, sizeof(Taxing), 1, fp) == 1) {
        if (strcmp(rec.name, sea_r) == 0) {
            printf("%s %.2f %.2f\n", rec.name, rec.income, rec.tax);
            fclose(fp);
            return;
        }
    }
    
    printf("Error: record not found.\n");

    fclose(fp);
}

void editing() {
    char sea[50];
    Taxing rec;
    FILE *fp;
    long int position;
    

    printf("Enter name to edit: ");
    scanf("%s", sea);
    
    fp = fopen(FN, "r+");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    while (fread(&rec, sizeof(Taxing), 1, fp) == 1) {
        if (strcmp(rec.name, sea) == 0) {
            position = ftell(fp) - sizeof(Taxing);
            printf("Enter new income: ");
            scanf("%f", &rec.income);
  
            if (rec.income <= 250000) {
        rec.tax = 0;
    } else if (rec.income <= 500000 && rec.income > 250000 ) {
        rec.tax = (rec.income *0.05);
    } else if (rec.income <= 750000 && rec.income > 500000) {
        rec.tax = (rec.income *0.01);
	} else if (rec.income <= 1000000 && rec.income > 750000) {
        rec.tax = (rec.income *0.15);
	} else if (rec.income <= 1250000 && rec.income > 1000000) {
        rec.tax = (rec.income *0.2);
	} else if (rec.income <= 1500000 && rec.income > 1250000) {
        rec.tax = (rec.income *0.25);				    
    } else {
        rec.tax = (rec.income *0.3);
    }
            fseek(fp, position, SEEK_SET);
            fwrite(&rec, sizeof(Taxing), 1, fp);
            printf("Record updated successfully.\n");
            fclose(fp);
            return;
        }
    }
    printf("Error: record not found.\n");
    fclose(fp);
}

void deleting() {
    char sea[50];
    Taxing rec;
    FILE *fp;
    FILE *tfp;
    int found = 0;
    printf("Enter name to delete: ");
    scanf("%s", sea);
    fp = fopen(FN, "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    tfp = fopen("tmp.txt", "w");
    if (tfp == NULL) {
        printf("Error: could not open temporary file.\n");
        fclose(fp);
        return;
    }
    while (fread(&rec, sizeof(Taxing), 1, fp) == 1) {
        if (strcmp(rec.name, sea) != 0) {
            fwrite(&rec, sizeof(Taxing), 1, tfp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(tfp);
    remove(FN);
    rename("tmp.txt", FN);
    if (found) {
        printf("Record deleted successfully.\n");
    } else {
        printf("Error: record not found.\n");
    }
}

int main() {
    int choice;
    
    while (1) {
    printf("1. Add New Record\n");
    printf("2. List all Tax Payer along with income tax to be paid\n");
    printf("3. Search\n");
    printf("4. Edit\n");
    printf("5. Delete Record\n");
    printf("6. Exit\n");
    printf("Enter choice:"); 
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            adding();
            break;
        case 2:
            listing();
            break;
        case 3:
            searching();
            break;
        case 4:
            editing();
            break;
        case 5:
            deleting();
            break;
        case 6:
            printf("Exited program\n");
            return 0;
        default:
            printf("Invalid choice.\n");
    }
}
}

