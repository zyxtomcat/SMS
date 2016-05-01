/*
Navicat MySQL Data Transfer

Source Server         : 虚拟机
Source Server Version : 50620
Source Host           : localhost:3306
Source Database       : db_sas

Target Server Type    : MYSQL
Target Server Version : 50620
File Encoding         : 65001

Date: 2016-04-21 18:05:06
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for t_ISMG_Info
-- ----------------------------
DROP TABLE IF EXISTS `t_ISMG_Info`;
CREATE TABLE `t_ISMG_Info` (
  `id` int(11) NOT NULL,
  `SP_Id` varchar(6) DEFAULT NULL,
  `server_host` varchar(24) DEFAULT NULL,
  `server_port` smallint(6) unsigned DEFAULT NULL,
  `protocol` varchar(6) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for t_ISMG_param
-- ----------------------------
DROP TABLE IF EXISTS `t_ISMG_param`;
CREATE TABLE `t_ISMG_param` (
  `SP_Id` varchar(6) NOT NULL,
  `param_key` varchar(16) DEFAULT NULL,
  `param_value` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`SP_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for t_num_segment
-- ----------------------------
DROP TABLE IF EXISTS `t_num_segment`;
CREATE TABLE `t_num_segment` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `Src_Id` varchar(22) NOT NULL COMMENT '短信接入号',
  `SP_Id` varchar(6) DEFAULT NULL COMMENT '企业代码',
  `begin_num` varchar(22) DEFAULT NULL COMMENT '开始号码',
  `end_num` varchar(22) DEFAULT NULL COMMENT '结束号码',
  `sum` int(11) unsigned DEFAULT NULL COMMENT '总数',
  `customer_id` int(11) DEFAULT NULL COMMENT '客户ID',
  `create_time` datetime DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time` datetime DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for t_sms_log
-- ----------------------------
DROP TABLE IF EXISTS `t_sms_log`;
CREATE TABLE `t_sms_log` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `Msg_Id` bigint DEFAULT NULL COMMENT 'Msg id',
  `SP_Id` varchar(6) DEFAULT NULL COMMENT '企业代码',
  `Src_Id` varchar(22) NOT NULL COMMENT '短信接入号',
  `Dst_Id` varchar(22) NOT NULL COMMENT '接收(下行)/发送(上行)号码(SIM卡号)',
  `sms_content` varchar(512) DEFAULT NULL COMMENT '短信内容',
  `sms_content_hex` varchar(512) DEFAULT NULL COMMENT '短信内容16进制',
  `pk_total` smallint unsigned DEFAULT NULL COMMENT '短信分包个数',
  `sms_fmt` tinyint DEFAULT 8 COMMENT '短信格式',
  `sms_type` bit DEFAULT 0 COMMENT '0-下行， 1-上行',
  `report_state` varchar(8) DEFAULT NULL COMMENT '状态报告',
  `report_time` datetime DEFAULT NULL COMMENT '状态报告时间',
  `done_time` datetime DEFAULT NULL COMMENT '目标收到时间',
  `create_time` datetime DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time` datetime DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
