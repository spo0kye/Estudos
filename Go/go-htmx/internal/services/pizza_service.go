package services

import (
	"go-htmx/internal/models"
	"go-htmx/internal/repositories"
)

func ListPizzas() ([]models.Pizza, error) {
	return repositories.GetAllPizzas()
}

func AddPizza(name string, price float64) error {
	pizza := models.Pizza{
		Name:  name,
		Price: price,
	}

	return repositories.CreatePizza(pizza)
}

func FindPizza(name string) models.Pizza {
	pizza, err := repositories.FindPizza(name)
	if err != nil {
		panic("Pizza not found")
	}

	return pizza
}
