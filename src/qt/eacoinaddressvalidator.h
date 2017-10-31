// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EACOIN_QT_EACOINADDRESSVALIDATOR_H
#define EACOIN_QT_EACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class EACoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EACoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** EACoin address widget validator, checks for a valid eacoin address.
 */
class EACoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit EACoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // EACOIN_QT_EACOINADDRESSVALIDATOR_H
