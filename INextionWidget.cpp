/*! \file */

#include "INextionWidget.h"

/*!
 * \brief Create a new widget adapter.
 * \param nex Reference to the Nextion driver
 * \param page ID of page this widget is on
 * \param component Component ID of this widget
 * \param name Name of this widget
 */
INextionWidget::INextionWidget(Nextion &nex, uint8_t page, uint8_t component,
                               const String &name)
    : m_nextion(nex)
    , m_pageID(page)
    , m_componentID(component)
    , m_name(name)
{
}

/*!
 * \brief Gets the ID of the page this widget resides on.
 * \return Page ID
 */
uint8_t INextionWidget::getPageID()
{
  return m_pageID;
}

/*!
 * \brief Gets the component ID of this widget.
 * \return Component ID
 */
uint8_t INextionWidget::getComponentID()
{
  return m_componentID;
}

/*!
 * \brief Sets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setNumberProperty(const String &propertyName, uint32_t value)
{
  return sendCommand(m_name + "." + propertyName + "=" + String(value));
}

/*!
 * \brief Gets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \return Value (may also return 0 in case of error)
 */
uint32_t INextionWidget::getNumberProperty(const String &propertyName)
{
  sendCommand("get " + m_name + "." + propertyName, false);
  uint32_t id;
  if (m_nextion.receiveNumber(&id))
    return id;
  else
    return 0;
}

/*!
 * \brief Sets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setStringProperty(const String &propertyName, const String &value)
{
  return sendCommand(m_name + "." + propertyName + "=\"" + value + "\"");
}

/*!
 * \brief Gets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Pointer to char array to store result in
 * \param len Maximum length of value
 * \return Actual length of value
 */
size_t INextionWidget::getStringProperty(const String &propertyName, char *value,
                                         size_t len)
{
  sendCommand("get " + m_name + "." + propertyName, false);
  return m_nextion.receiveString(value, len);
}

bool INextionWidget::sendCommand(const String &commandStr, bool checkComplete)
{
  m_nextion.sendCommand(commandStr);

  if (checkComplete)
    return m_nextion.checkCommandComplete();
  else
    return true;
}
