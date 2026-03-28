package repositories

import (
	"go-htmx/internal/database"
	"go-htmx/internal/models"
)

func GetAllPizzas() ([]models.Pizza, error) {
	var pizzas []models.Pizza
	result := database.DB.Find(&pizzas)

	return pizzas, result.Error
}

func CreatePizza(pizza models.Pizza) error {
	result := database.DB.Create(&pizza)
	return result.Error
}

func FindPizza(name string) (models.Pizza, error) {
	var pizza = models.Pizza{Name: name}
	result := database.DB.Find(&pizza)

	return pizza, result.Error
}
