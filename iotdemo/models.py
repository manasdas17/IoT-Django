import datetime

from django.utils import timezone
from django.db import models


class Customer(models.Model):
  username = models.CharField(max_length=128)
  email = models.CharField(max_length=128, unique=True)
  
  def __str__(self):
    return self.username


class Cake(models.Model):
  label = models.CharField(max_length=128)
  price = models.IntegerField(default=0)
  quantity = models.IntegerField(default=0)
  deviceid = models.CharField(max_length=128) 
  
  def __str__(self):
    return self.label


class Order(models.Model):
  customer = models.ForeignKey(Customer)
  cake = models.ForeignKey(Cake)
  date = models.DateTimeField(auto_now_add=True, blank=True)
  number = models.IntegerField(default=0)
  earnings = models.IntegerField(default=0)


# Cakes are added/managed in the main Admin panel by the store owner. 
# Currently does not group together Orders with different Cakes but in the same checkout. 
# Currently also does not allow image uploads for the different Cakes. 

