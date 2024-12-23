package main

import (
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"fmt"
)

type Category struct {
	ID       uint      	`gorm:"primaryKey"`
	Name     string    	`gorm:"not null"`
	Products []Product  `gorm:"foreignKey:CategoryID"`
}

type Product struct {
	ID         uint    `gorm:"primaryKey"`
	Name       string  `gorm:"not null"`
	Price      float64 `gorm:"not null"`
	CategoryID uint
}

func main() {
	dsn := "host=localhost user=postgres password=3121 dbname=mydb port=5432 sslmode=disable"
	// db, _ := grom.Open(postgres.Open(dsn), &gorm.Config{})
	db, err := gorm.Open(postgres.Open(dsn), &gorm.Config{})

	if err != nil {
		panic("не удалось подключиться к бд")
	}

	db.AutoMigrate(&Category{}, &Product{})

	// Create
	someCat := Category{
		Name: "Category 1",
		Products: []Product{
			Product{Name: "Product 1", Price: 999.99},
			Product{Name: "Product 2", Price: 1999.99},
		},
	}

	db.Create(&someCat)


	// Read
	var categories []Category

	db.Preload("Products").Find(&categories)

	for _, cat := range categories {
		fmt.Printf("Category: %s\n", cat.Name)
		for _, product := range cat.Products {
			fmt.Printf("\t- Product: %s,\tPrice: %.2f\n", product.Name, product.Price)
		}
	}

	// Update and Read
	var product Product
	
	db.First(&product, "name = ?", "Product 1")
	product.Price *= 1.1
	db.Save(&product)

	fmt.Println("Updated")
	db.Preload("Products").Find(&categories)

	for _, cat := range categories {
		fmt.Printf("Category: %s\n", cat.Name)
		for _, product := range cat.Products {
			fmt.Printf("\t- Product: %s,\tPrice: %.2f\n", product.Name, product.Price)
		}
	}

	// Delete
	var categoryToDelete Category
	db.Preload("Products").First(&categoryToDelete, "name = ?", "Category 1")
	db.Delete(&categoryToDelete.Products)
	db.Delete(&categoryToDelete)
}
