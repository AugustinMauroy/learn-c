#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct {
    unsigned int day;
    unsigned int month;
    int year;
} date;

/**
 * Parse une date
 * Format: dd/mm/yyyy
 */
date parseDate(char *str) {
    date d;
    char *token = strtok(str, "/");

    if (token != NULL) {
        d.day = atoi(token);
        token = strtok(NULL, "/");
        if (token != NULL) {
            d.month = atoi(token);
            token = strtok(NULL, "/");
            if (token != NULL) {
                d.year = atoi(token);
            }
        }
    }

    return d;
}

/**
 * Nombre de jours écoulé depuis 1/01/1970
 * Note: 1 année = 365 jours
 *       1 mois = 30 jours
 *       1 jour = 24 heures
 *       1 heure = 60 minutes
 *       1 minute = 60 secondes
 */
long epoch(void) {
    long t = time(NULL);
    return t / (24 * 60 * 60);
}

/**
 * Vérifie si une année est bissextile
 * Note: Divisible par 4 et non divisible par 100 ou divisible par 400
 */
bool isBissextile(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Différence entre les deux dates en jours
 */
unsigned int diffDate(date a, date b) {
    unsigned short int qdays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    date oldest = a;
    date newest = b;
    unsigned int totalDaysA = 0, totalDaysB = 0;

    if (a.year > b.year || (a.year == b.year && (a.month > b.month || (a.month == b.month && a.day > b.day)))) {
        oldest = b;
        newest = a;
    }

    // Calculate total days for the oldest date
    for (int year = 0; year < oldest.year; year++) {
        totalDaysA += isBissextile(year) ? 366 : 365;
    }
    for (int month = 1; month < oldest.month; month++) {
        totalDaysA += qdays[month];
    }
    totalDaysA += oldest.day;

    // Calculate total days for the newest date
    for (int year = 0; year < newest.year; year++) {
        totalDaysB += isBissextile(year) ? 366 : 365;
    }
    for (int month = 1; month < newest.month; month++) {
        totalDaysB += qdays[month];
    }
    totalDaysB += newest.day;

    // Adjust for leap year in the current year if the date is past February
    if (isBissextile(oldest.year) && oldest.month > 2) {
        totalDaysA += 1;
    }
    if (isBissextile(newest.year) && newest.month > 2) {
        totalDaysB += 1;
    }

    return totalDaysB - totalDaysA;
}

/**
 * Vérifie si une date est valide
 */
bool isValideDate(date d) {
    unsigned short int qdays[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    qdays[2] = isBissextile(d.year) ? 29 : 28;

    if (d.month < 1 || d.month > 12) return false;

    if (d.day < 1 || d.day > qdays[d.month]) return false;

    return true;
}

/**
 * Initialise une date à la date actuelle
 */
void newDate(date *d) {
    long days = epoch();

    int year = 1970;
    while (days >= 365) {
        if (isBissextile(year)) {
            if (days >= 366) {
                days -= 366;
            } else {
                break;
            }
        } else {
            days -= 365;
        }
        year++;
    }

    int month = 1;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isBissextile(year)) daysInMonth[2] = 29;

    while (days >= daysInMonth[month]) {
        days -= daysInMonth[month];
        month++;
    }

    int day = days + 1;

    d->day = day;
    d->month = month;
    d->year = year;
}

void displayDate(date d) {
    printf("{\n");
    printf("\t\"day\": \033[33m%d\033[0m,\n", d.day);
    printf("\t\"month\": \033[33m%d\033[0m,\n", d.month);
    printf("\t\"year\": \033[33m%d\033[0m\n", d.year);
    printf("}\n");
}
