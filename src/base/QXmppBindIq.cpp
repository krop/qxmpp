// SPDX-FileCopyrightText: 2011 Manjeet Dahiya <manjeetdahiya@gmail.com>
// SPDX-FileCopyrightText: 2010 Jeremy Lainé <jeremy.laine@m4x.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "QXmppBindIq.h"

#include "QXmppConstants_p.h"
#include "QXmppUtils.h"

#include <QDomElement>
#include <QTextStream>
#include <QXmlStreamWriter>

/// Returns the bound JID.
///

QString QXmppBindIq::jid() const
{
    return m_jid;
}

/// Sets the bound JID.
///
/// \param jid

void QXmppBindIq::setJid(const QString &jid)
{
    m_jid = jid;
}

/// Returns the requested resource.
///

QString QXmppBindIq::resource() const
{
    return m_resource;
}

/// Sets the requested resource.
///
/// \param resource

void QXmppBindIq::setResource(const QString &resource)
{
    m_resource = resource;
}

/// \cond
bool QXmppBindIq::isBindIq(const QDomElement &element)
{
    QDomElement bindElement = element.firstChildElement(QStringLiteral("bind"));
    return (bindElement.namespaceURI() == ns_bind);
}

void QXmppBindIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement bindElement = element.firstChildElement(QStringLiteral("bind"));
    m_jid = bindElement.firstChildElement(QStringLiteral("jid")).text();
    m_resource = bindElement.firstChildElement(QStringLiteral("resource")).text();
}

void QXmppBindIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement(QStringLiteral("bind"));
    writer->writeDefaultNamespace(ns_bind);
    if (!m_jid.isEmpty()) {
        helperToXmlAddTextElement(writer, QStringLiteral("jid"), m_jid);
    }
    if (!m_resource.isEmpty()) {
        helperToXmlAddTextElement(writer, QStringLiteral("resource"), m_resource);
    }
    writer->writeEndElement();
}
/// \endcond
