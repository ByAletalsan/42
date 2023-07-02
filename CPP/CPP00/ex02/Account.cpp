/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:54:39 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/02 11:57:00 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount= 0;
int Account::_totalNbDeposits= 0;
int Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts( void )
{
    return (_nbAccounts);
}

int	Account::getTotalAmount( void )
{
    return (_totalAmount);
}

int	Account::getNbDeposits( void )
{
    return (_totalNbDeposits);
}

int	Account::getNbWithdrawals( void )
{
    return (_totalNbWithdrawals);
}

void	Account::displayAccountsInfos( void )
{
    _displayTimestamp();
    std::cout << "accounts:" << getNbAccounts() << std::flush;
    std::cout << ";total:" << getTotalAmount() << std::flush;
    std::cout << ";deposits:" << getNbDeposits() << std::flush;
    std::cout << ";withdrawals:" << getNbWithdrawals() << std::flush;
    std::cout << std::endl;
}

void	Account::_displayTimestamp( void )
{
    std::time_t result = std::time(NULL);

    std::cout << std::setfill('0') <<"[" << 1900 + std::localtime(&result)->tm_year
    << std::setw(2) << 1 + std::localtime(&result)->tm_mon
    <<  std::setw(2) << std::localtime(&result)->tm_mday
    <<  "_"
    <<  std::setw(2) << std::localtime(&result)->tm_hour
    <<  std::setw(2) << std::localtime(&result)->tm_min
    <<  std::setw(2) << std::localtime(&result)->tm_sec 
    << "] " << std::flush;
}

Account::Account( int initial_deposit )
{
    this->_accountIndex = _nbAccounts;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;
    _nbAccounts++;
    _totalAmount += initial_deposit;
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << std::flush;
    std::cout << ";amount:" << this->_amount << std::flush;
    std::cout << ";created" << std::endl;
}

Account::~Account( void )
{
    _nbAccounts--;
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << std::flush;
    std::cout << ";amount:" << this->_amount << std::flush;
    std::cout << ";closed" << std::endl;
}

void	Account::makeDeposit( int deposit )
{
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << std::flush;
    std::cout << ";p_amount:" << this->_amount << std::flush;
    std::cout << ";deposit:" << deposit << std::flush;
    this->_amount += deposit;
    this->_nbDeposits++;
    _totalNbDeposits++;
    _totalAmount += deposit;
    std::cout << ":amount:" << this->_amount << std::flush;
    std::cout << ";nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << std::flush;
    std::cout << ";p_amount:" << this->_amount << std::flush;
    std::cout << ";withdrawal:" << std::flush;
    if (withdrawal > checkAmount())
    {
        std::cout << "refused" << std::endl;
        return (false);
    }
    std::cout << withdrawal << std::flush;
    this->_amount -= withdrawal;
    this->_nbWithdrawals++;
    _totalNbWithdrawals++;
    _totalAmount -= withdrawal;
    std::cout << ":amount:" << this->_amount << std::flush;
    std::cout << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return (true);
}

int		Account::checkAmount( void ) const
{
    return (this->_amount);
}

void	Account::displayStatus( void ) const
{
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << std::flush;
    std::cout << ";amount:" << this->_amount << std::flush;
    std::cout << ":deposits:" << this->_nbDeposits << std::flush;
    std::cout << ";withdrawals:" << this->_nbWithdrawals << std::endl;
}
