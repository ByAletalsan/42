# Generated by Django 4.2.5 on 2024-04-07 19:17

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('data_app', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='matchhistory',
            name='mode',
            field=models.CharField(max_length=25),
        ),
    ]