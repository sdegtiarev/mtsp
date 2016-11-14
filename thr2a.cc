
_M_pi->_M_use_count++;
if(--_M_pi->_M_use_count == 0)
  _M_pi->_M_dispose();
